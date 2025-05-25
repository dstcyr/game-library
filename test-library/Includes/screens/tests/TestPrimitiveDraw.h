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

#ifndef SCREENS_TESTS_TESTPRIMITIVEDRAWS_H
#define SCREENS_TESTS_TESTPRIMITIVEDRAWS_H

#include "screens/ScreenState.h"

class TestPrimitiveDraw : public ScreenState
{
public:
    void Enter() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    size_t m_Font = 0;
    size_t m_Bg = 0;
    size_t m_Hero = 0;
    float m_Angle = 0.0F;
    float m_MouseX = 0.0F;
    float m_MouseY = 0.0F;
    bool m_MouseDown = false;
};

#endif
