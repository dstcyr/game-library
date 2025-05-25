//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef UTILS_ISTATE_H
#define UTILS_ISTATE_H

class IState
{
public:
    virtual ~IState() = default;
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update(float dt) = 0;
    virtual bool ProcessInput(float dt) = 0;
    virtual void Draw() = 0;
};

#endif
