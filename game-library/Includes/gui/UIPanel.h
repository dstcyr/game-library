//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UIPANEL_H
#define GUI_UIPANEL_H

#include "gui/UINode.h"
#include "graphics/SpriteSheet.h"

class UIPanel : public UINode
{
public:
    void Initialize(const std::string& filename, float width, float height, float border);
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void SetChild(UINode* node);
    void SetFitContent(bool fit);
    void SetPadding(float x, float y);
    void Clear() override;

private:
    UINode* m_Child = nullptr;
    SpriteSheet m_Image;
    float m_Width = 0.0F;
    float m_Height = 0.0F;
    float m_Border = 0.0F;
    bool m_FitContent = false;
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;
};

#endif
