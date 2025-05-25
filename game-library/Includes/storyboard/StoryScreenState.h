//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_STORYSCREENSTATE_H
#define STORYBOARD_STORYSCREENSTATE_H

#include <cstdint>
#include "StoryState.h"

class StoryScreenState : public StoryState
{
public:
    static StoryState* Create(Storyboard* screen, const std::string& id, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    bool ProcessInput(float dt) override;
    void Draw() override;
    void SetAlpha(uint8_t alpha);

private:
    StoryScreenState(Storyboard* screen, const std::string& id, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

#endif
