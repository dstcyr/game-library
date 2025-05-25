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

#ifndef COMBAT_ENEMYHURT_H
#define COMBAT_ENEMYHURT_H

#include "ICombatState.h"

class CombatScreen;
class CombatActor;

class EnemyHurt : public ICombatState
{
public:
    EnemyHurt();
    EnemyHurt(CombatScreen* screen, CombatActor* actor, CombatActor* target);

    void Enter() override;
    bool ProcessInput(float deltaTime) override;
    void Update(float deltaTime) override;
    void Draw() override;
    bool IsFinished() override;

private:
    CombatScreen* m_Screen;
    CombatActor* m_Actor;
    CombatActor* m_Target;
    bool m_IsFinished = false;
    float m_Elapsed = 0.0F;
    float m_Duration = 0.1F;
    float m_OriginalX = 0.0F;
    float m_OriginalY = 0.0F;
};

#endif
