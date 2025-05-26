//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H

#include <string>
#include "maths/Rect.h"

class Sprite
{
public:
    virtual ~Sprite() = default;
    virtual void Load(const std::string& filename);
    virtual void Draw(const Rect<float>& bounds);
    virtual void Draw(float x, float y, float w, float h, float angle);
    virtual void Draw(float x, float y, float angle);
    void GetSize(int* width, int* height) const;
    void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

protected:
    size_t m_TextureId = 0;
    Rect<int> m_Source{ 0, 0, 0, 0 };
    unsigned char m_Red = 255;
    unsigned char m_Green = 255;
    unsigned char m_Blue = 255;
    unsigned char m_Alpha = 255;
};

#endif
