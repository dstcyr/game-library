//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "controllers/Controller.h"
#include "controllers/ControllerState.h"

void Controller::Add(const std::string& name, ControllerState* state)
{
    m_ControllerMap[name] = state;
}

void Controller::Set(const std::string& name)
{
    if (m_IsPaused)
    {
        return;
    }

    if (m_ControllerMap.count(name) > 0)
    {
        if (m_CurrentState != nullptr)
        {
            m_CurrentState->OnExit(this);
        }

        m_CurrentState = m_ControllerMap[name];
        m_CurrentState->OnEnter(this);
    }
}

void Controller::Initialize(Entity* character)
{
    m_Entity = character;
}

bool Controller::ProcessInput(float delta)
{
    if (m_IsPaused)
    {
        return true;
    }

    if (m_CurrentState != nullptr)
    {
        return m_CurrentState->OnProcessInput(delta, this);
    }

    return true;
}

void Controller::Update(float delta)
{
    if (m_IsPaused)
    {
        return;
    }

    if (m_CurrentState != nullptr)
    {
        m_CurrentState->OnUpdate(delta, this);
    }
}

void Controller::Clear()
{
    for (auto itr = m_ControllerMap.begin(); itr != m_ControllerMap.end(); ++itr)
    {
        delete itr->second;
    }

    m_ControllerMap.clear();
    m_CurrentState = nullptr;
}

void Controller::Pause()
{
    m_IsPaused = true;
    m_CurrentState = nullptr;
}

void Controller::Resume(const std::string& stateName)
{
    m_IsPaused = false;
    Set(stateName);
}
