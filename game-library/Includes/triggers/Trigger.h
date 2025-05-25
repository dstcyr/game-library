//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef TRIGGERS_TRIGGER_H
#define TRIGGERS_TRIGGER_H

class IAction;
class Entity;

class Trigger
{
public:
    void SetOnEnterAction(IAction* action);
    void SetOnExitAction(IAction* action);
    void SetOnUseAction(IAction* action);
    void OnEnter(Entity* entity);
    void OnExit(Entity* entity);
    void OnUse(Entity* entity);
    void Clear();

private:
    IAction* m_OnEnterAction = nullptr;
    IAction* m_OnExitAction = nullptr;
    IAction* m_OnUseAction = nullptr;
};

#endif
