//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_CAPTIONSTATE_H
#define STORYBOARD_CAPTIONSTATE_H

#include <cstdint>
#include "StoryState.h"

struct FCaptionStyle
{
    std::string font;
    int size = 24;
    bool centerH = true;
    bool centerV = true;
    float x = 0.0F;
    float y = 0.0F;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t alpha = 255;
};

class CaptionState : public StoryState
{
public:
    CaptionState(Storyboard* screen, const std::string& id, const std::string& style, const std::string& text);

    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    bool ProcessInput(float dt) override;
    void Draw() override;

private:
    size_t m_Font = 0;
    std::string m_Style;
    std::string m_Text;
    std::map<std::string, FCaptionStyle> m_Styles;
    float m_X = 0.0F;
    float m_Y = 0.0F;
};

#endif
