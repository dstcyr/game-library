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

#ifndef SCREENS_UIPROGRESSTEXT_H
#define SCREENS_UIPROGRESSTEXT_H

#include "gui/UINode.h"
#include "gui/UIImage.h"
#include "gui/UIHorizontalBox.h"
#include "gui/UIVerticalBox.h"
#include "gui/UIText.h"
#include "gui/UIProgress.h"
#include "gui/UISeparator.h"

class UIProgressText : public UINode
{
public:
    void Initialize();
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void SetPadding(float x, float y);
    void SetInfo(int current, int maxValue);

private:
    UIHorizontalBox m_HBox;
    UIText m_TextValue;
    UIProgress m_ProgressBar;
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;
};

#endif
