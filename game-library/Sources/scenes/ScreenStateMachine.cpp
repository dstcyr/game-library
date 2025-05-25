//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "scenes/ScreenStateMachine.h"
#include "screens/ScreenState.h"
#include "save/BufferedFile.h"
#include "scenes/StackCommands.h"

void ScreenStateMachine::RegisterState(const std::string& name, ScreenState* state)
{
    m_StateDatabase.emplace(name, state);
}

bool ScreenStateMachine::ProcessInput(float deltaTime)
{
    if (!m_RuntimeStack.IsEmpty())
    {
        ScreenState* lastState = m_RuntimeStack.Last();
        return lastState->ProcessInput(deltaTime);
    }

    return true;
}

void ScreenStateMachine::Update(float deltaTime)
{
    if (!m_RuntimeStack.IsEmpty())
    {
        ScreenState* lastState = m_RuntimeStack.Last();
        lastState->Update(deltaTime);
    }

    ExecuteCommands();
    m_Fade.Update(deltaTime);
}

void ScreenStateMachine::Draw()
{
    // if (!m_RuntimeStack.IsEmpty())
    // {
    //     ScreenState* state = m_RuntimeStack.Last();
    //     state->Draw();
    // }

    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        ScreenState* state = *it;
        state->Draw();
    }
}

void ScreenStateMachine::PostDraw()
{
    m_Fade.Draw();
}

void ScreenStateMachine::Save(BufferedFile* saveFile)
{
    int stackCount = m_RuntimeStack.Count();
    saveFile->WriteInt32(stackCount);

    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        std::string stateName = FindNameOfInstance(*it);
        saveFile->WriteString(stateName);
    }
}

void ScreenStateMachine::SaveState(BufferedFile* saveFile)
{
    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        (*it)->Save(saveFile);
    }
}

void ScreenStateMachine::Load(BufferedFile* saveFile)
{
    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        (*it)->Exit();
    }

    m_RuntimeStack.Clear();

    int stackCount = 0;
    saveFile->ReadInt32(&stackCount);

    for (int i = 0; i < stackCount; i++)
    {
        std::string stateName;
        saveFile->ReadString(stateName);

        if (m_SaveBlacklist.count(stateName) == 0)
        {
            ScreenState* state = m_StateDatabase[stateName];
            m_RuntimeStack.PushBack(state);
            state->Enter();
        }
    }
}

void ScreenStateMachine::LoadState(BufferedFile* saveFile)
{
    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        (*it)->Load(saveFile);
    }
}

void ScreenStateMachine::Push(const std::string& name)
{
    if (m_StateDatabase.count(name) > 0)
    {
        ScreenState* state = m_StateDatabase[name];
        m_StateCommands.PushBack(new PushCommand(state));
    }
}

void ScreenStateMachine::Pop()
{
    m_StateCommands.PushBack(new PopCommand());
}

void ScreenStateMachine::Replace(const std::string& name)
{
    if (m_StateDatabase.count(name) > 0)
    {
        ScreenState* state = m_StateDatabase[name];
        m_StateCommands.PushBack(new ReplaceCommand(state));
    }
}

void ScreenStateMachine::Change(const std::string& name)
{
    ClearCommands();
    if (m_StateDatabase.count(name) > 0)
    {
        ScreenState* state = m_StateDatabase[name];
        m_StateCommands.PushBack(new ChangeCommand(state));
    }
}

void ScreenStateMachine::FadeTo(const std::string& name, bool startWithBlackScreen)
{
    ClearCommands();
    if (m_StateDatabase.count(name) > 0)
    {
        ScreenState* state = m_StateDatabase[name];
        m_StateCommands.PushBack(new FadeCommand(state, startWithBlackScreen));
    }
}

void ScreenStateMachine::InternalPushState(ScreenState* state)
{
    BX_CHECKS(state != nullptr, "Cannot push null state");

    if (!m_RuntimeStack.IsEmpty())
    {
        ScreenState* lastState = m_RuntimeStack.Last();
        lastState->Pause();
    }

    state->Enter();
    m_RuntimeStack.PushBack(state);
}

void ScreenStateMachine::InternalPopState()
{
    BX_CHECKS(!m_RuntimeStack.IsEmpty(), "Cannot pop a state from an empty stack");

    ScreenState* state = m_RuntimeStack.PopBack();
    state->Exit();

    if (!m_RuntimeStack.IsEmpty())
    {
        state = m_RuntimeStack.Last();
        state->Resume();
    }
}

void ScreenStateMachine::InternalChange(ScreenState* state)
{
    BX_CHECKS(state != nullptr, "Cannot change to null state");

    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        (*it)->Exit();
    }

    m_RuntimeStack.Clear();
    m_RuntimeStack.PushBack(state);
    state->Enter();
}

void ScreenStateMachine::InternalFadeToState(ScreenState* state, bool startWithBlackScreen)
{
    BX_CHECKS(state != nullptr, "Cannot change to null state");

    m_Fade.Init(startWithBlackScreen);

    if (startWithBlackScreen)
    {
        InternalChange(state);
        FadeIn();
    }
    else
    {
        FadeOut([this, state]()
            {
                InternalChange(state);
                FadeIn();
            }
        );
    }
}

void ScreenStateMachine::InternalReplaceTop(ScreenState* state)
{
    BX_CHECKS(!m_RuntimeStack.IsEmpty(), "Cannot pop a state from an empty stack");

    ScreenState* lastState = m_RuntimeStack.PopBack();
    lastState->Exit();

    state->Enter();
    m_RuntimeStack.PushBack(state);
}

void ScreenStateMachine::ClearCommands()
{
    while (!m_StateCommands.IsEmpty())
    {
        IStackCommand* command = m_StateCommands.PopBack();
        delete command;
    }
}

void ScreenStateMachine::ExecuteCommands()
{
    while (!m_StateCommands.IsEmpty())
    {
        IStackCommand* command = m_StateCommands.PopBack();
        command->Execute(this);
        delete command;
    }
}

void ScreenStateMachine::Clear()
{
    m_RuntimeStack.Clear();

    for (auto itr = m_StateDatabase.begin(); itr != m_StateDatabase.end(); ++itr)
    {
        itr->second->Destroy();
        delete itr->second;
    }

    m_StateDatabase.clear();
    ClearCommands();
}

void ScreenStateMachine::FadeIn()
{
    m_Fade.FadeIn();
}

void ScreenStateMachine::FadeOut(const std::function<void()>& callback)
{
    m_Fade.FadeOut(callback, true);
}

FStateInfo ScreenStateMachine::GetStateInfo()
{
    bool bTopState = true;

    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        FStateInfo info = (*it)->GetStateInfo();
        if (info.hasInfo)
        {
            info.isTopState = bTopState;
            return info;
        }

        bTopState = false;
    }

    FStateInfo info;
    info.hasInfo = false;
    info.isTopState = false;
    info.mapName.clear();
    return info;
}

std::string ScreenStateMachine::GetTileType(int x, int y)
{
    ScreenState* last = m_RuntimeStack.Last();
    return last->GetTileType(x, y);
}

std::string ScreenStateMachine::FindNameOfInstance(ScreenState* inst)
{
    for (auto it = m_StateDatabase.begin(); it != m_StateDatabase.end(); it++)
    {
        if (it->second == inst)
        {
            return it->first;
        }
    }

    return {};
}
