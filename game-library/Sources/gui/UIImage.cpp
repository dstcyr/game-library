//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UIImage.h"

void UIImage::Initialize(const std::string& filename, float width, float height)
{
    m_Image.Load(filename);

    m_Width = width;
    m_Height = height;
}

void UIImage::Initialize(const std::string& filename)
{
    m_Image.Load(filename);

    int width = 0;
    int height = 0;
    m_Image.GetSize(&width, &height);

    m_Width = static_cast<float>(width);
    m_Height = static_cast<float>(height);
}

void UIImage::Scale(float scalar)
{
    m_Width *= scalar;
    m_Height *= scalar;
}

void UIImage::Draw(float posX, float posY)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Image.Draw(posX + m_PaddingX, posY + m_PaddingY, m_Width, m_Height, 0.0F);

#if defined(DEBUG_UI)
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 255, 255, 0, 255);
#endif
}

float UIImage::GetWidth() const
{
    return m_Width + m_PaddingX + m_PaddingX;
}

float UIImage::GetHeight() const
{
    return m_Height + m_PaddingY + m_PaddingY;
}

void UIImage::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}
