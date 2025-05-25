//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UIPROGRESS_H
#define GUI_UIPROGRESS_H

#include "UINode.h"
#include <cinttypes>

class UIProgress : public UINode
{
public:
    void Initialize(float width, float height);
    float GetWidth() const override;
    float GetHeight() const override;
    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void Draw(float posX, float posY) override;
    void SetProgress(float progress);
    void SetPadding(float x, float y);
    void SetBorder(float border);

private:
    float m_Progress = 0.0F;
    float m_Width = 0.0F;
    float m_Height = 0.0F;
    float m_Border = 2.0F;
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;

    uint8_t m_ForegroundRed = 0;
    uint8_t m_ForegroundGreen = 0;
    uint8_t m_ForegroundBlue = 0;
    uint8_t m_ForegroundAlpha = 255;
};

#endif
