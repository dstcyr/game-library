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

#ifndef GUI_UIITEMENTRY_H
#define GUI_UIITEMENTRY_H

#include "gui/UINode.h"
#include "gui/UIText.h"
#include "gui/UIImage.h"
#include "gui/UIHorizontalBox.h"

class UIItemEntry : public UINode
{
public:
    static UINode* Create(const std::string& text, int stack, const std::string& image, const std::string& frame);

    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;

private:
    UIText m_ItemText;
    UIText m_StackText;
    UIImage m_ItemImage;
    UIHorizontalBox m_ItemBox;
};

#endif
