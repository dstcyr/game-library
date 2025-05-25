//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_FADEEVENT_H
#define STORYBOARD_FADEEVENT_H

#include "IStoryboardEvent.h"

class Storyboard;
class StoryScreenState;

class FadeEvent : public IStoryboardEvent
{
public:
    explicit FadeEvent(Storyboard* screen, bool block);

protected:
    Storyboard* m_Screen = nullptr;
    float m_Elapsed = 0.0F;
    float m_FadeSpeed = 0.01F;
    int m_FadeInc = 2;
    int m_FadeAlpha = 255;
};

#endif
