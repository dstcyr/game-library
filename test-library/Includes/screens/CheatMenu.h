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

#ifndef SCREENS_CHEATMENU_H
#define SCREENS_CHEATMENU_H

#include "screens/ScreenState.h"
#include "gui/UIPanel.h"
#include "gui/UIVerticalBox.h"
#include "gui/UIHorizontalBox.h"
#include "gui/UIText.h"
#include "gui/UIImage.h"
#include "UIPartyEntry.h"

class CheatMenu : public ScreenState
{
public:
    void Enter() override;
    bool ProcessInput(float deltaTime) override;
    void Draw() override;

private:
    UIPanel m_TopTitlePanel;
    UIPanel m_OptionPanel;
    UIVerticalBox m_Options;

    UIText m_DamageText;
    UIText m_HealText;
    UIText m_XpText;
    UIText m_MegaXpText;
    UIText m_ThiefUnlock;
    UIText m_MageUnlock;
    UIText m_StartCombat;
    UIText m_StartStory;

    UIText m_TitleText;

    UIImage m_CursorImage;

    std::vector<float> m_OptionList;
    int m_SelectedOption = 0;

    float m_TitlePosX = 0.0F;
    bool m_Initialized = false;

    UIVerticalBox m_MainBox;
};

#endif
