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

#ifndef SCREENS_TESTS_TESTUI_H
#define SCREENS_TESTS_TESTUI_H

#include "screens/ScreenState.h"
#include "gui/UIText.h"
#include "gui/UIImage.h"
#include "gui/UIProgress.h"
#include "gui/UIPanel.h"
#include "gui/UIVerticalBox.h"
#include "gui/UISeparator.h"
#include "gui/UIHorizontalBox.h"

class TestUI : public ScreenState
{
public:
    void Enter() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    size_t m_Font = 0;

    UIText m_TextTest;
    UIImage m_ImageTest;
    UIProgress m_ProgressTest;
    UIPanel m_PanelTest;
    UIVerticalBox m_VerticalTest;
    UIHorizontalBox m_HorizontalTest;
    UISeparator m_VerticalSeparatorTest;
    UISeparator m_HorizontalSeparatorTest;
};

#endif
