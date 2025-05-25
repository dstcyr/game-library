//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "utils/StateStack.h"
#include "utils/IState.h"
#include "utils/Checks.h"
#include "utils/StateStackCommands.h"

void StateStack::Update(float dt)
{
    if (!m_RuntimeStack.IsEmpty())
    {
        IState* lastState = m_RuntimeStack.Last();
        lastState->Update(dt);
    }

    ExecuteCommands();
}

bool StateStack::ProcessInput(float dt)
{
    if (!m_RuntimeStack.IsEmpty())
    {
        IState* lastState = m_RuntimeStack.Last();
        return lastState->ProcessInput(dt);
    }

    return true;
}

void StateStack::Draw()
{
    // if (!m_RuntimeStack.IsEmpty())
    // {
    //     IState* state = m_RuntimeStack.Last();
    //     state->Draw();
    // }

    // if (!m_RuntimeStack.IsEmpty())
    // {
    //     int cnt = m_RuntimeStack.Count() - 1;
    //     for (int i = cnt; i >= 0; i--)
    //     {
    //         m_RuntimeStack.At(i)->Draw();
    //     }
    // }

    if (!m_RuntimeStack.IsEmpty())
    {
        int cnt = m_RuntimeStack.Count();
        for (int i = 0; i < cnt; i++)
        {
            m_RuntimeStack.At(i)->Draw();
        }
    }
}

void StateStack::Push(IState* state)
{

    m_StateCommands.PushBack(new PushStateCommand(state));
}

void StateStack::Pop()
{
    m_StateCommands.PushBack(new PopStateCommand());
}

void StateStack::Replace(IState* state)
{
    m_StateCommands.PushBack(new ReplaceStateCommand(state));
}

void StateStack::Change(IState* state)
{
    ClearCommands();
    m_StateCommands.PushBack(new ChangeStateCommand(state));
}

IState* StateStack::Last()
{
    return m_RuntimeStack.Last();
}

IState* StateStack::First()
{
    return m_RuntimeStack.First();
}

void StateStack::Clear()
{
    while (!m_RuntimeStack.IsEmpty())
    {
        IState* state = m_RuntimeStack.PopBack();
        delete state;
    }
}

void StateStack::Remove(std::function<bool(const IState*)> predicate)
{
    m_RuntimeStack.Remove(predicate);
}

void StateStack::InternalPushState(IState* state)
{
    BX_CHECKS(state != nullptr, "Cannot push null state");

    state->Enter();
    m_RuntimeStack.PushBack(state);
}

void StateStack::InternalPopState()
{
    BX_CHECKS(!m_RuntimeStack.IsEmpty(), "Cannot pop a state from an empty stack");

    IState* state = m_RuntimeStack.PopBack();
    state->Exit();
}

void StateStack::InternalChange(IState* state)
{
    BX_CHECKS(state != nullptr, "Cannot change to null state");

    for (auto it = m_RuntimeStack.Begin(); it != m_RuntimeStack.End(); it++)
    {
        (*it)->Exit();
    }

    m_RuntimeStack.Clear();

    state->Enter();
    m_RuntimeStack.PushBack(state);
}

void StateStack::InternalReplaceTop(IState* state)
{
    BX_CHECKS(!m_RuntimeStack.IsEmpty(), "Cannot pop a state from an empty stack");

    IState* lastState = m_RuntimeStack.PopBack();
    lastState->Exit();

    state->Enter();
    m_RuntimeStack.PushBack(state);
}

void StateStack::ClearCommands()
{
    while (!m_StateCommands.IsEmpty())
    {
        IStateStackCommand* command = m_StateCommands.PopBack();
        delete command;
    }
}

void StateStack::ExecuteCommands()
{
    while (!m_StateCommands.IsEmpty())
    {
        IStateStackCommand* command = m_StateCommands.PopBack();
        command->Execute(this);
        delete command;
    }
}
