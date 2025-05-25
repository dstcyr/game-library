//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/WaitEvent.h"

IStoryboardEvent* WaitEvent::Create(float seconds)
{
    IStoryboardEvent* newEvent = new WaitEvent(seconds);
    return newEvent;
}

WaitEvent::WaitEvent(float seconds) :
    IStoryboardEvent(true),
    m_Seconds(seconds)
{
}

void WaitEvent::Update(float deltaTime)
{
    m_Seconds = MathUtils::Max(0.0F, m_Seconds - deltaTime);
    m_Finished = m_Seconds <= 0.0F;
}
