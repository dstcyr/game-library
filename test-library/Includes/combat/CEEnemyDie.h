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

#ifndef COMBAT_CEENEMYDIE_H
#define COMBAT_CEENEMYDIE_H

#include "ICombatState.h"
#include "ICombatEvent.h"

class CombatScreen;
class CombatActor;

class CEEnemyDie : public ICombatEvent
{
public:
    CEEnemyDie();
    CEEnemyDie(CombatActor* owner, CombatScreen* screen);

    void Execute(CombatEventQueue* eventQueue) override;
    void Update(float deltaTime) override;
    bool IsFinished() override;
    float GetCountDown() const override;
    void SetCountDown(float countdown) override;
    float GetTimePoints(CombatEventQueue* eventQueue) override;
    std::string GetName() override;

private:
    CombatScreen* m_Screen;
    CombatActor* m_Actor;
    CombatEventQueue* m_Queue;

    bool m_IsFinished = false;
    float m_Elapsed = 0.0F;
    float m_Duration = 0.0F;
};

#endif
