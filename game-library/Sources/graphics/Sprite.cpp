//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "graphics/Sprite.h"

void Sprite::Draw(float x, float y, float w, float h, float angle)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    Rect<float> dst(x, y, w, h);
    tGraphics.DrawImage(m_TextureId, m_Source, dst, angle, false, false, m_Red, m_Green, m_Blue, m_Alpha);
}

void Sprite::Draw(float x, float y, float angle)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    Rect<float> dst(x, y, static_cast<float>(m_Source.width), static_cast<float>(m_Source.height));
    tGraphics.DrawImage(m_TextureId, m_Source, dst, angle, false, false, m_Red, m_Green, m_Blue, m_Alpha);

#if defined(DEBUG_SPRITE)
    tGraphics.DrawRect(x, y, m_Source.width, m_Source.height, 255, 255, 0, 255);
#endif
}

void Sprite::GetSize(int* width, int* height) const
{
    *width = m_Source.width;
    *height = m_Source.height;
}

void Sprite::SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    m_Red = red;
    m_Green = green;
    m_Blue = blue;
    m_Alpha = alpha;
}

void Sprite::Load(const std::string& filename)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    m_TextureId = tGraphics.LoadTexture(filename);
    tGraphics.GetImageSize(m_TextureId, &m_Source.width, &m_Source.height);
}
