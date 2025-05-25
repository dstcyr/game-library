//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "scenes/StackCommands.h"
#include "scenes/ScreenStateMachine.h"
#include "screens/ScreenState.h"

PushCommand::PushCommand(ScreenState* stateToPush) :
    m_State(stateToPush)
{
}

void PushCommand::Execute(ScreenStateMachine* fsm)
{
    BX_CHECKS(fsm != nullptr, "State Machine is null");
    fsm->InternalPushState(m_State);
}

void PopCommand::Execute(ScreenStateMachine* fsm)
{
    BX_CHECKS(fsm != nullptr, "State Machine is null");
    fsm->InternalPopState();
}

ChangeCommand::ChangeCommand(ScreenState* state) :
    m_State(state)
{
}

void ChangeCommand::Execute(ScreenStateMachine* fsm)
{
    BX_CHECKS(fsm != nullptr, "State Machine is null");
    fsm->InternalChange(m_State);
}

ReplaceCommand::ReplaceCommand(ScreenState* state) :
    m_State(state)
{
}

void ReplaceCommand::Execute(ScreenStateMachine* fsm)
{
    BX_CHECKS(fsm != nullptr, "State Machine is null");
    fsm->InternalReplaceTop(m_State);
}

FadeCommand::FadeCommand(ScreenState* state, bool startWithBlackScreen) :
    m_State(state),
    m_StartWithBlackScreen(startWithBlackScreen)
{
}

void FadeCommand::Execute(ScreenStateMachine* fsm)
{
    BX_CHECKS(fsm != nullptr, "State Machine is null");
    fsm->InternalFadeToState(m_State, m_StartWithBlackScreen);
}
