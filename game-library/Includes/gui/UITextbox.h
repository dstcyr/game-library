//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UITEXTBOX_H
#define GUI_UITEXTBOX_H

#include "UINode.h"
#include "UIPanel.h"
#include "UIText.h"
#include <vector>
#include <string>
#include <functional>

class UITextbox : public UINode
{
public:
    static UITextbox* Create(const std::string& text, float posX, float posY);

    bool ProcessInput(float deltaTime) override;
    void Draw() override;
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void Clear() override;

private:
    UIPanel m_Panel;
    UIText m_Text;
    float m_PosX = 0.0F;
    float m_PosY = 0.0F;
};

#endif
