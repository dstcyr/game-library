//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef CONTROLLERS_CONTROLLERSTATE_H
#define CONTROLLERS_CONTROLLERSTATE_H

class Entity;
class Controller;

class ControllerState
{
public:
    explicit ControllerState(std::string nextState) : m_NextState(std::move(nextState)) {}
    virtual ~ControllerState() = default;
    virtual void OnEnter(Controller* controller) {}
    virtual void OnExit(Controller* controller) {}
    virtual void OnUpdate(float dt, Controller* controller) {}
    virtual bool OnProcessInput(float dt, Controller* controller) { return true; }

protected:
    std::string m_NextState;
};

#endif
