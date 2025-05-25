//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef UTILS_STATESTACKCOMMANDS_H
#define UTILS_STATESTACKCOMMANDS_H

class StateStack;
class IState;

class IStateStackCommand
{
public:
    virtual ~IStateStackCommand() = default;
    virtual void Execute(StateStack* stateStack) = 0;
};

class PushStateCommand : public IStateStackCommand
{
public:
    explicit PushStateCommand(IState* stateToPush);
    void Execute(StateStack* stateStack) override;

private:
    IState* m_State = nullptr;
};

class PopStateCommand : public IStateStackCommand
{
public:
    void Execute(StateStack* stateStack) override;
};

class ChangeStateCommand : public IStateStackCommand
{
public:
    explicit ChangeStateCommand(IState* state);
    void Execute(StateStack* stateStack) override;

private:
    IState* m_State = nullptr;
};

class ReplaceStateCommand : public IStateStackCommand
{
public:
    explicit ReplaceStateCommand(IState* state);
    void Execute(StateStack* stateStack) override;

private:
    IState* m_State = nullptr;
};

#endif
