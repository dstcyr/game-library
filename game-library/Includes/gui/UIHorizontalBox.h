//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UIHORIZONTALBOX_H
#define GUI_UIHORIZONTALBOX_H

#include "UIBox.h"

class UIHorizontalBox : public UIBox
{
public:
    float GetWidth() const override;
    float GetHeight() const override;
    void Draw(float posX, float posY) override;
    void SetPadding(float x, float y);

private:
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;
};

#endif
