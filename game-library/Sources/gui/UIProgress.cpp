//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UIProgress.h"

void UIProgress::Initialize(float width, float height)
{
    m_Width = width;
    m_Height = height;
}

float UIProgress::GetWidth() const
{
    return m_Width + m_PaddingX + m_PaddingX;
}

float UIProgress::GetHeight() const
{
    return m_Height + m_PaddingY + m_PaddingY;
}

void UIProgress::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    m_ForegroundRed = r;
    m_ForegroundGreen = g;
    m_ForegroundBlue = b;
    m_ForegroundAlpha = a;
}

void UIProgress::Draw(float posX, float posY)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.FillRect(posX + m_PaddingX, posY + m_PaddingY, m_Width, m_Height, 255, 255, 255, 255);
    tGraphics.FillRect(posX + m_PaddingX + m_Border, posY + m_PaddingY + m_Border, m_Width - m_Border - m_Border, m_Height - m_Border - m_Border, 45, 45, 45, 255);
    tGraphics.FillRect(posX + m_PaddingX + m_Border, posY + m_PaddingY + m_Border, (m_Width - m_Border - m_Border) * m_Progress, m_Height - m_Border - m_Border,
        m_ForegroundRed, m_ForegroundGreen, m_ForegroundBlue, m_ForegroundAlpha);

#if defined(DEBUG_UI)
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 255, 255, 0, 255);
#endif
}

void UIProgress::SetProgress(float progress)
{
    m_Progress = progress;
    if (m_Progress < 0.0F)
    {
        m_Progress = 0.0F;
    }
    else if(m_Progress > 1.0F)
    {
        m_Progress = 1.0F;
    }
}

void UIProgress::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}

void UIProgress::SetBorder(float border)
{
    m_Border = border;
}
