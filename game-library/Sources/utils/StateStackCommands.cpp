//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "utils/StateStackCommands.h"
#include "utils/Checks.h"
#include "utils/StateStack.h"

PushStateCommand::PushStateCommand(IState* stateToPush) :
    m_State(stateToPush)
{
}

void PushStateCommand::Execute(StateStack* stateStack)
{
    BX_CHECKS(stateStack != nullptr, "State Machine is null");
    stateStack->InternalPushState(m_State);
}

void PopStateCommand::Execute(StateStack* stateStack)
{
    BX_CHECKS(stateStack != nullptr, "State Machine is null");
    stateStack->InternalPopState();
}

ChangeStateCommand::ChangeStateCommand(IState* state) :
    m_State(state)
{
}

void ChangeStateCommand::Execute(StateStack* stateStack)
{
    BX_CHECKS(stateStack != nullptr, "State Machine is null");
    stateStack->InternalChange(m_State);
}

ReplaceStateCommand::ReplaceStateCommand(IState* state) :
    m_State(state)
{
}

void ReplaceStateCommand::Execute(StateStack* stateStack)
{
    BX_CHECKS(stateStack != nullptr, "State Machine is null");
    stateStack->InternalReplaceTop(m_State);
}
