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

#ifndef SCREENS_UIPARTYENTRY_H
#define SCREENS_UIPARTYENTRY_H

#include "gui/UINode.h"
#include "gui/UIImage.h"
#include "gui/UIHorizontalBox.h"
#include "gui/UIVerticalBox.h"
#include "gui/UIText.h"
#include "gui/UIProgress.h"
#include "gui/UISeparator.h"

struct FCharacterDefinition;

class UIPartyEntry : public UINode
{
public:
    void Initialize();
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void SetPadding(float x, float y);
    void SetInfo(const FCharacterDefinition* definition);

private:
    UIHorizontalBox m_EntryBox;
    UIVerticalBox m_TextBox;
    UIImage m_Portrait;
    UIText m_Name;
    UIText m_Level;
    UIText m_Hp;
    UIText m_Mp;

    UIVerticalBox m_NextLevelBox;
    UIVerticalBox m_HpBox;
    UIVerticalBox m_MpBox;
    UIText m_NextLevel;
    UISeparator m_NextLevelSeparator;
    UISeparator m_InfoSeparator;
    UIProgress m_NextLevelProgress;
    UIProgress m_HPProgress;
    UIProgress m_MPProgress;
    float m_PaddingX = 0.0F;
    float m_PaddingY = 0.0F;
};

#endif
