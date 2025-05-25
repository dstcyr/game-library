//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UISEPARATOR_H
#define GUI_UISEPARATOR_H

#include "UINode.h"

class UISeparator : public UINode
{
public:
    void Initialize(float w, float h);
    float GetWidth() const override;
    float GetHeight() const override;
    void Draw(float posX, float posY) override;

private:
    float m_Width = 0.0F;
    float m_Height = 0.0F;
};

#endif
