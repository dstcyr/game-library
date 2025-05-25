//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef UTILS_STATESTACK_H
#define UTILS_STATESTACK_H

#include "data/Stack.h"

class IState;
class IStateStackCommand;

class StateStack
{
public:
    void Update(float dt);
    bool ProcessInput(float dt);
    void Draw();
    void Push(IState* state);
    void Pop();
    void Replace(IState* state);
    void Change(IState* state);
    IState* Last();
    IState* First();
    void Clear();
    void Remove(std::function<bool(const IState*)> predicate);

    auto Begin() { return m_RuntimeStack.Begin(); }
    auto End() { return m_RuntimeStack.End(); }

private:
    friend class PushStateCommand;
    friend class PopStateCommand;
    friend class ChangeStateCommand;
    friend class ReplaceStateCommand;

    TArray<IState> m_RuntimeStack;
    TArray<IStateStackCommand> m_StateCommands;

    void InternalPushState(IState* state);
    void InternalPopState();
    void InternalChange(IState* state);
    void InternalReplaceTop(IState* state);
    void ClearCommands();
    void ExecuteCommands();
};

#endif
