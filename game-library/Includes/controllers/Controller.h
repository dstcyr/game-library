//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef CONTROLLERS_CONTROLLER_H
#define CONTROLLERS_CONTROLLER_H

#include "scenes/Blackboard.h"

class Entity;
class ControllerState;

class Controller
{
public:
    void Add(const std::string& name, ControllerState* state);
    void Set(const std::string& name);
    void Initialize(Entity* character);
    bool ProcessInput(float delta);
    void Update(float delta);
    void Clear();

    void Pause();
    void Resume(const std::string& stateName);

    Entity* GetEntity() { return m_Entity; }
    Blackboard* GetBlackboard() { return &m_Blackboard; }

private:
    std::map<std::string, ControllerState*> m_ControllerMap;
    ControllerState* m_CurrentState{ nullptr };
    Entity* m_Entity{ nullptr };
    Blackboard m_Blackboard;
    bool m_IsPaused = false;
};

#endif
