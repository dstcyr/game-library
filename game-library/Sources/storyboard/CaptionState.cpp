//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/CaptionState.h"

CaptionState::CaptionState(Storyboard* screen, const std::string& id, const std::string& style, const std::string& text) :
    StoryState(screen, id, 0, 0, 0, 0), m_Style(style), m_Text(text)
{
    // std::string font;
    // int size = 24;
    // bool centerH = true;
    // bool centerV = true;
    // float x = 0.0F;
    // float y = 0.0F;
    // uint8_t red = 0;
    // uint8_t green = 0;
    // uint8_t blue = 0;
    // uint8_t alpha = 255;

    FCaptionStyle title;
    title.font = "fonts/junction.ttf";
    title.size = 70;
    title.centerH = true;
    title.centerV = false;
    title.x = 0.0F;
    title.y = 300.0F;
    title.red = 255;
    title.green = 255;
    title.blue = 255;
    title.alpha = 255;

    m_Styles.emplace("title", title);

    FCaptionStyle subtitle;
    subtitle.font = "fonts/junction.ttf";
    subtitle.size = 45;
    subtitle.centerH = true;
    subtitle.centerV = false;
    subtitle.x = 0.0F;
    subtitle.y = 400.0F;
    subtitle.red = 200;
    subtitle.green = 200;
    subtitle.blue = 150;
    subtitle.alpha = 255;

    m_Styles.emplace("subtitle", subtitle);
}

void CaptionState::Enter()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    m_ScreenWidth = static_cast<float>(screenW);
    m_ScreenHeight = static_cast<float>(screenH);

    FCaptionStyle captionStyle = m_Styles[m_Style];
    m_Red = captionStyle.red;
    m_Green = captionStyle.green;
    m_Blue = captionStyle.blue;
    m_Alpha = captionStyle.alpha;

    m_Font = tGraphics.LoadFont(captionStyle.font, captionStyle.size);

    int textW = 0;
    int textH = 0;
    tGraphics.GetTextSize(m_Text, m_Font, &textW, &textH);

    if (captionStyle.centerH)
    {
        m_X = (static_cast<float>(screenW) / 2.0F) - (static_cast<float>(textW) / 2.0F);
    }
    else
    {
        m_X = captionStyle.x;
    }

    if (captionStyle.centerV)
    {
        m_Y = (static_cast<float>(screenH) / 2.0F) - (static_cast<float>(textH) / 2.0F);
    }
    else
    {
        m_Y = captionStyle.y;
    }
}

void CaptionState::Exit()
{
}

void CaptionState::Update(float dt)
{
}

bool CaptionState::ProcessInput(float dt)
{
    return true;
}

void CaptionState::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    tGraphics.EnableCamera(false);

    FCaptionStyle captionStyle = m_Styles[m_Style];
    tGraphics.DrawString(m_Text, m_Font, m_X, m_Y, m_Red, m_Green, m_Blue, m_Alpha);
    tGraphics.EnableCamera(true);
}
