//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/WaitStateEvent.h"
#include "storyboard/StoryState.h"

IStoryboardEvent* WaitStateEvent::Create(StoryState* state)
{
    IStoryboardEvent* newEvent = new WaitStateEvent(state);
    return newEvent;
}

WaitStateEvent::WaitStateEvent(StoryState* state) :
    IStoryboardEvent(true),
    m_State(state)
{
}

void WaitStateEvent::Update(float deltaTime)
{
    m_Finished = m_State->IsReady();
}
