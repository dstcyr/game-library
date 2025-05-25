//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UIText.h"

void UIText::Initialize(const std::string& fontFile, int fontSize, float width, float height)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont(fontFile, fontSize);
    m_Width = width;
    m_Height = height;
    m_FitContent = (m_Width == 0 && m_Height == 0);
}

void UIText::Draw(float posX, float posY)
{
    IGraphics& tGraphics = Game::Get().Graphics();

    float locationX = GetAlignedX(posX);
    float locationY = GetAlignedY(posY);

    tGraphics.DrawString(m_Text, m_Font, locationX, locationY, m_WrapLength, m_Red, m_Green, m_Blue, m_Alpha);


#if defined(DEBUG_UI)
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 255, 255, 0, 255);
#endif
}

float UIText::GetWidth() const
{
    IGraphics& tGraphics = Game::Get().Graphics();

    if (m_WrapLength > 0)
    {
        return m_WrapLength + m_PaddingX + m_PaddingX;
    }

    if (m_FitContent)
    {
        int w = 0;
        int h = 0;
        tGraphics.GetTextSize(m_Text, m_Font, &w, &h);
        return w + m_PaddingX + m_PaddingX;
    }

    return m_Width;
}

float UIText::GetHeight() const
{
    IGraphics& tGraphics = Game::Get().Graphics();
    int w = 0;
    int h = 0;
    tGraphics.GetTextSize(m_Text, m_Font, &w, &h);

    if (m_WrapLength > 0)
    {
        auto lines = static_cast<int>(std::ceil(w / static_cast<float>(m_WrapLength)));
        return (h * lines) + m_PaddingY + m_PaddingY;
    }

    if (m_FitContent)
    {
        return h + m_PaddingY + m_PaddingY;
    }

    return m_Height;
}

void UIText::SetFitContent(bool fit)
{
    m_FitContent = fit;
}

void UIText::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    m_Red = r;
    m_Green = g;
    m_Blue = b;
    m_Alpha = a;
}

void UIText::SetText(const std::string& text)
{
    m_Text = text;
}

void UIText::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}

void UIText::SetWrap(int wrapLength)
{
    m_WrapLength = wrapLength;
}

void UIText::SetAlign(EHAlignContent hAlign, EVAlignContent vAlign)
{
    m_HAlign = hAlign;
    m_VAlign = vAlign;
}

float UIText::GetAlignedX( float posX)
{
    if (m_WrapLength > 0)
    {
        return posX + m_PaddingX;
    }

    IGraphics& tGraphics = Game::Get().Graphics();

    int w = 0;
    int h = 0;
    tGraphics.GetTextSize(m_Text, m_Font, &w, &h);
    float totalWidth = GetWidth();
    float locationX = posX;

    switch (m_HAlign)
    {
    case EHAlignContent::RIGHT:
    {
        float newLocation = totalWidth - static_cast<float>(w);
        locationX = posX + newLocation - m_PaddingX;
        break;
    }
    case EHAlignContent::CENTER:
    {
        float newLocation = (totalWidth / 2.0F) - (static_cast<float>(w) / 2.0F);
        locationX = posX + newLocation;
        break;
    }
    default:
    {
        locationX = posX + m_PaddingX;
        break;
    }
    }

    return locationX;
}

float UIText::GetAlignedY(float posY)
{
    if (m_WrapLength > 0)
    {
        return posY + m_PaddingY;
    }

    IGraphics& tGraphics = Game::Get().Graphics();

    int w = 0;
    int h = 0;
    tGraphics.GetTextSize(m_Text, m_Font, &w, &h);
    float totalHeight = GetHeight();
    float locationY = posY;

    switch (m_VAlign)
    {
    case EVAlignContent::BOTTOM:
    {
        float newLocation = totalHeight - static_cast<float>(h);
        locationY = posY + newLocation - m_PaddingY;
        break;
    }
    case EVAlignContent::MIDDLE:
    {
        float newLocation = (totalHeight / 2.0F) - (static_cast<float>(h) / 2.0F);
        locationY = posY + newLocation;
        break;
    }
    default:
    {
        locationY = posY + m_PaddingY;
        break;
    }
    }

    return locationY;
}
