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

#ifndef SCREENS_TESTS_TESTINTERPOLATIONS_H
#define SCREENS_TESTS_TESTINTERPOLATIONS_H

#include "screens/ScreenState.h"

class TestInterpolations : public ScreenState
{
public:
    void Enter() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    size_t m_Font = 0;
    float m_LinearX = 0.0F;
    float m_CircularInX = 0.0F;
    float m_CircularOutX = 0.0F;
    float m_CircularInOutX = 0.0F;
    float m_SinusoidalInX = 0.0F;
    float m_SinusoidalInOutX = 0.0F;
    float m_SinusoidalOutX = 0.0F;
    float m_BackInX = 0.0F;
    float m_BackOutX = 0.0F;
    float m_BackInOutX = 0.0F;
    float m_BounceInX = 0.0F;
    float m_BounceOutX = 0.0F;
    float m_BounceInOutX = 0.0F;
    float m_ElasticInX = 0.0F;
    float m_ElasticOutX = 0.0F;
    float m_ElasticInOutX = 0.0F;
    float m_ScreenW = 0.0F;
    float m_ScreenH = 0.0F;
    float m_Dest = 0.0F;
    float m_Duration = 5.0F;
    float m_Elapsed = 0.0F;
};

#endif
