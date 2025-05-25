//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UINODE_H
#define GUI_UINODE_H

#include <cinttypes>

enum class EHAlignContent : uint8_t
{
    LEFT,
    RIGHT,
    CENTER
};

enum class EVAlignContent : uint8_t
{
    TOP,
    MIDDLE,
    BOTTOM
};

class UINode
{
public:
    virtual ~UINode() = default;

    virtual void Draw() { Draw(0.0F, 0.0F); }
    virtual void Update(float deltaTime) {}
    virtual bool ProcessInput(float dt) { return true; }
    virtual void Clear() {}

    virtual void Draw(float posX, float posY) = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;
};

#endif
