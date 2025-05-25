//  
//     _ ____  ____   ____   ____            _        
//    (_)  _ \|  _ \ / ___| |  _ \ _ __ ___ | |_ ___  
//    | | |_) | |_) | |  _  | |_) | '__/ _ \| __/ _ \ 
//    | |  _ <|  __/| |_| | |  __/| | | (_) | || (_) |
//   _/ |_| \_\_|    \____| |_|   |_|  \___/ \__\___/ 
//  |__/                                              
//  
//  jRPG Prototype
//  Copyright(C) 2024-2025 David St-Cyr
//  
//  The information in this file is confidential and solely for the attention
//  and use of the author. You are hereby notified that any dissemination,
//  distribution or copy of this content is prohibited without the prior
//  written consent of the author.
//
//  David St-Cyr
//  st-cyrdavid@hotmail.com

#ifndef GUI_UINOTIFICATION_H
#define GUI_UINOTIFICATION_H

#include "gui/UINode.h"
#include "gui/UIPanel.h"
#include "gui/UIText.h"

class UINotification : public UINode
{
public:
    static void Create(const std::string& text, float delay);

    void Update(float deltaTime) override;
    void Draw() override;
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;

private:
    UIPanel m_NoticePanel;
    UIText m_NoticeText;
    float m_PosX = 0.0F;
    float m_PosY = 0.0F;
    float m_Delay = 0.0F;
    float m_Elapsed = 0.0F;
};

#endif
