//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UITEXT_H
#define GUI_UITEXT_H

#include "UINode.h"
#include <string>

class UIText : public UINode
{
public:
    void Initialize(const std::string& fontFile, int fontSize, float width = 0.0F, float height = 0.0F);
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void SetFitContent(bool fit);
    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void SetText(const std::string& text);
    void SetPadding(float x, float y);
    void SetWrap(int wrapLength);
    void SetAlign(EHAlignContent hAlign, EVAlignContent vAlign);

private:
    float GetAlignedX(float posX);
    float GetAlignedY(float posY);

    size_t m_Font = 0;
    std::string m_Text;
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;
    int m_WrapLength = 0;
    float m_Width = 0.0F;
    float m_Height = 0.0F;
    bool m_FitContent = false;
    EHAlignContent m_HAlign = EHAlignContent::LEFT;
    EVAlignContent m_VAlign = EVAlignContent::TOP;

    uint8_t m_Red = 0;
    uint8_t m_Green = 0;
    uint8_t m_Blue = 0;
    uint8_t m_Alpha = 255;
};

#endif
