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

#ifndef SCREENS_GAMEMENU_H
#define SCREENS_GAMEMENU_H

#include "screens/ScreenState.h"
#include "gui/UIPanel.h"
#include "gui/UIVerticalBox.h"
#include "gui/UIHorizontalBox.h"
#include "gui/UIText.h"
#include "gui/UIImage.h"
#include "UIPartyEntry.h"

class GameMenu : public ScreenState
{
public:
    void Enter() override;
    bool ProcessInput(float deltaTime) override;
    void Draw() override;
    void Exit() override;
    void Destroy() override;

private:
    void UpdateHintText();

    UIPanel m_TopTitlePanel;
    UIPanel m_OptionPanel;
    UIPanel m_InfoPanel;
    UIPanel m_PartyPanel;
    UIPanel m_HintPanel;

    UIVerticalBox m_MenuBox;
    UIVerticalBox m_OptionBox;
    UIHorizontalBox m_BottomBox;

    UIVerticalBox m_Options;
    UIText m_ItemsText;
    UIText m_StatusText;
    UIText m_SaveText;
    UIText m_LoadText;
    UIText m_QuitText;

    UIText m_TitleText;
    UIText m_HintText;

    UIImage m_CursorImage;

    std::vector<float> m_OptionList;
    int m_SelectedOption = 0;

    float m_TitlePosX = 0.0F;
    bool m_Initialized = false;

    UIVerticalBox m_PartyBox;
    UIVerticalBox m_MainBox;

    std::vector<UIPartyEntry*> m_PartyEntries;
};

#endif
