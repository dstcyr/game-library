//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GRAPHICS_SPRITESHEET_H
#define GRAPHICS_SPRITESHEET_H

#include "Sprite.h"
#include <map>

class SpriteSheet : public Sprite
{
public:
    void Draw(float x, float y);
    void Draw(float x, float y, float w, float h);
    void Draw(const std::string& frame, float x, float y);
    void Draw(const std::string& frame, float x, float y, float w, float h);
    void AddFrame(const std::string& name, int x, int y, int w, int h);
    void SetFrame(const std::string& name);

private:
    std::map<std::string, Rect<int>> m_Frames;
};

#endif
