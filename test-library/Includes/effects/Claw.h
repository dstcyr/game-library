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

#ifndef EFFECTS_CLAW_H
#define EFFECTS_CLAW_H

#include "combat/IEffect.h"

class Character;

class Claw : public IEffect
{
public:
    static IEffect* Create(Character* target);

    void Update(float deltaTime) override;
    void Draw() override;
    bool IsFinished() override;

private:
    Character* m_Target = nullptr;
    Animation m_Animation;
    float m_X = 0.0F;
    float m_Y = 0.0F;
    int m_Priority = 0;
    bool m_IsFinished = false;
};

#endif
