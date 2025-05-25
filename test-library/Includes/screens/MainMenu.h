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

#ifndef SCREENS_MAINMENU_H
#define SCREENS_MAINMENU_H

#include "screens/ScreenState.h"
#include "gui/UIImage.h"
#include "gui/UIText.h"
#include "gui/UIVerticalBox.h"

class MainMenu : public ScreenState
{
public:
    void Enter() override;
    bool ProcessInput(float deltaTime) override;
    void Draw() override;
    void Exit() override;

private:
    UIVerticalBox m_OptionBox;
    UIText m_PlayText;
    UIText m_LoadText;
    UIText m_ExitText;
    UIText m_VersionText;
    UIVerticalBox m_TitleBox;
    UIImage m_TitleImage;
    UIImage m_CursorImage;
    UIText m_SubTitleText;
    float m_TitlePosX = 0.0F;
    float m_OptionPosX = 0.0F;
    std::vector<std::pair<float, float>> m_Options;
    int m_SelectedOption = 0;
    bool m_SaveFileFound = false;
};

#endif
