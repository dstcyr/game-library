//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_FADEINEVENT_H
#define STORYBOARD_FADEINEVENT_H

#include "FadeEvent.h"

class Storyboard;
class StoryScreenState;

class FadeInEvent : public FadeEvent
{
public:
    static FadeEvent* Create(Storyboard* screen, const std::string& id, bool block);

    explicit FadeInEvent(Storyboard* screen, const std::string& target, bool block);
    void Update(float deltaTime) override;

private:
    std::string m_TargetId;
};

#endif
