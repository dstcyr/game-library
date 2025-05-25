//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_STORYSTATE_H
#define STORYBOARD_STORYSTATE_H

#include "utils/IState.h"
#include <cstdint>
#include <string>

class Storyboard;

class StoryState : public IState
{
public:
    StoryState(Storyboard* screen, const std::string& id, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    bool ProcessInput(float dt) override;
    void Draw() override;
    void SetAlpha(uint8_t alpha);
    const std::string GetID() const { return m_Id; }
    bool IsReady() const { return m_IsReady; }

protected:
    std::string m_Id;
    uint8_t m_Red = 0;
    uint8_t m_Green = 0;
    uint8_t m_Blue = 0;
    uint8_t m_Alpha = 255;
    float m_ScreenWidth = 0.0F;
    float m_ScreenHeight = 0.0F;
    Storyboard* m_Screen = nullptr;
    bool m_IsReady = false;
};

#endif
