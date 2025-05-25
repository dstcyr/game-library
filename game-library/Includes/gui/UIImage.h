//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UIIMAGE_H
#define GUI_UIIMAGE_H

#include "UINode.h"
#include "graphics/Sprite.h"
#include <string>

class UIImage : public UINode
{
public:
    void Initialize(const std::string& filename, float width, float height);
    void Initialize(const std::string& filename);
    void Scale(float scalar);
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void SetPadding(float x, float y);

private:
    Sprite m_Image;
    float m_Width = 0.0F;
    float m_Height = 0.0F;
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;
};

#endif
