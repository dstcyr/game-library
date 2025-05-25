//  
//     _ ____  ____   ____   ____            _        
//    (_)  _ \|  _ \ / ___| |  _ \ _ __ ___ | |_ ___  
//    | | |_) | |_) | |  _  | |_) | '__/ _ \| __/ _ \ 
//    | |  _ <|  __/| |_| | |  __/| | | (_) | || (_) |
//   _/ |_| \_\_|    \____| |_|   |_|  \___/ \__\___/ 
//  |__/                                              
//  
//  jRPG Prototype
//  Copyright(C) 2024-2025 David St-Cyr
//  
//  The information in this file is confidential and solely for the attention
//  and use of the author. You are hereby notified that any dissemination,
//  distribution or copy of this content is prohibited without the prior
//  written consent of the author.
//
//  David St-Cyr
//  st-cyrdavid@hotmail.com

#include "Config.h"
#include "screens/UIProgressText.h"

void UIProgressText::Initialize()
{
    int menuFontSize = 28;
    m_TextValue.Initialize("fonts/junction.ttf", menuFontSize);
    m_TextValue.SetColor(255, 255, 255, 255);
    m_TextValue.SetPadding(5.0F, 5.0F);

    m_ProgressBar.Initialize(400.0F, 5.0F);
    m_ProgressBar.SetColor(255, 0, 0, 255);
    m_ProgressBar.SetPadding(5.0F, 15.0F);
    m_ProgressBar.SetBorder(0.0F);
    
    m_HBox.AddChild(&m_TextValue);
    m_HBox.AddChild(&m_ProgressBar);
}

void UIProgressText::Draw(float posX, float posY)
{
    m_HBox.Draw(posX + m_PaddingX, posY + m_PaddingY);

#if defined(DEBUG_UI)
    IGraphics& tGraphics = Game::Get().Graphics();
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 255, 0, 0, 255);
#endif
}

float UIProgressText::GetWidth() const
{
    return m_HBox.GetWidth() + m_PaddingX + m_PaddingX;
}

float UIProgressText::GetHeight() const
{
    return m_HBox.GetHeight() + m_PaddingY + m_PaddingY;
}

void UIProgressText::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}

void UIProgressText::SetInfo(int current, int maxValue)
{
    float percent = static_cast<float>(current) / static_cast<float>(maxValue);
    m_TextValue.SetText(std::to_string(current) + "/" + std::to_string(maxValue));
    m_ProgressBar.SetProgress(percent);
}
