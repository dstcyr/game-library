//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_WAITEVENT_H
#define STORYBOARD_WAITEVENT_H

#include "IStoryboardEvent.h"

class WaitEvent : public IStoryboardEvent
{
public:
    static IStoryboardEvent* Create(float seconds);

    explicit WaitEvent(float seconds);
    void Update(float deltaTime) override;

private:
    float m_Seconds = 0.0F;
};

#endif
