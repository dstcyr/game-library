//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

void SpriteSheet::Draw(float x, float y)
{
    Sprite::Draw(x, y, 0.0F);
}

void SpriteSheet::Draw(const std::string& frame, float x, float y)
{
    SetFrame(frame);
    Draw(x, y);
}

void SpriteSheet::Draw(float x, float y, float w, float h)
{
    Sprite::Draw(x, y, w, h, 0.0F);
}

void SpriteSheet::Draw(const std::string& frame, float x, float y, float w, float h)
{
    SetFrame(frame);
    Draw(x, y, w, h);
}

void SpriteSheet::AddFrame(const std::string& name, int x, int y, int w, int h)
{
    m_Frames.emplace(name, Rect<int>{ x, y, w, h });

    if (m_Frames.size() == 1)
    {
        SetFrame(name);
    }
}

void SpriteSheet::SetFrame(const std::string& name)
{
    Rect<int> src = m_Frames[name];
    m_Source.x = src.x;
    m_Source.y = src.y;
    m_Source.width = src.width;
    m_Source.height = src.height;
}
