//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "triggers/Trigger.h"
#include "triggers/IAction.h"

void Trigger::SetOnEnterAction(IAction* action)
{
    m_OnEnterAction = action;
}

void Trigger::SetOnExitAction(IAction* action)
{
    m_OnExitAction = action;
}

void Trigger::SetOnUseAction(IAction* action)
{
    m_OnUseAction = action;
}

void Trigger::OnEnter(Entity* entity)
{
    if (m_OnEnterAction != nullptr)
    {
        m_OnEnterAction->Execute(entity);
    }
}

void Trigger::OnExit(Entity* entity)
{
    if (m_OnExitAction != nullptr)
    {
        m_OnExitAction->Execute(entity);
    }
}

void Trigger::OnUse(Entity* entity)
{
    if (m_OnUseAction != nullptr)
    {
        m_OnUseAction->Execute(entity);
    }
}

void Trigger::Clear()
{
    delete m_OnEnterAction;
    m_OnEnterAction = nullptr;

    delete m_OnExitAction;
    m_OnExitAction = nullptr;

    delete m_OnUseAction;
    m_OnUseAction = nullptr;
}
