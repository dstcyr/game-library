//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_TIMEDTEXTBOXEVENT_H
#define STORYBOARD_TIMEDTEXTBOXEVENT_H

#include "IStoryboardEvent.h"
#include "gui/UIPanel.h"
#include "gui/UIText.h"

class Storyboard;
class StoryScreenState;
class UITextbox;

class TimedTextboxEvent : public IStoryboardEvent
{
public:
    explicit TimedTextboxEvent(Storyboard* screen, bool block, float x, float y);
    void Update(float deltaTime) override;

protected:
    Storyboard* m_Screen = nullptr;
    float m_Elapsed = 0.0F;

    UITextbox* m_Textbox;
};

#endif
