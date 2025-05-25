//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_STACKCOMMANDS_H
#define SCENES_STACKCOMMANDS_H

#include "screens/ScreenState.h"

class ScreenStateMachine;

class IStackCommand
{
public:
    virtual ~IStackCommand() = default;
    virtual void Execute(ScreenStateMachine* fsm) = 0;
};

class PushCommand : public IStackCommand
{
public:
    explicit PushCommand(ScreenState* stateToPush);
    void Execute(ScreenStateMachine* fsm) override;

private:
    ScreenState* m_State;
};

class PopCommand : public IStackCommand
{
public:
    void Execute(ScreenStateMachine* fsm) override;
};

class ChangeCommand : public IStackCommand
{
public:
    explicit ChangeCommand(ScreenState* state);
    void Execute(ScreenStateMachine* fsm) override;

private:
    ScreenState* m_State;
};

class ReplaceCommand : public IStackCommand
{
public:
    explicit ReplaceCommand(ScreenState* state);
    void Execute(ScreenStateMachine* fsm) override;

private:
    ScreenState* m_State;
};

class FadeCommand : public IStackCommand
{
public:
    explicit FadeCommand(ScreenState* state, bool startWithBlackScreen);
    void Execute(ScreenStateMachine* fsm) override;

private:
    ScreenState* m_State = nullptr;
    bool m_StartWithBlackScreen = false;
};

#endif
