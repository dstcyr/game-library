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

#ifndef COMBAT_CEATTACK_H
#define COMBAT_CEATTACK_H

#include "ICombatEvent.h"
#include <string>

class Character;
class CombatScreen;
class CombatActor;

class CEAttack : public ICombatEvent
{
public:
    CEAttack();
    CEAttack(CombatActor* owner, CombatActor* target, CombatScreen* screen);

    void Execute(CombatEventQueue* eventQueue) override;
    void Update(float deltaTime) override;
    bool IsFinished() override;
    void SetCountDown(float countdown) override;
    float GetCountDown() const override;
    float GetTimePoints(CombatEventQueue* eventQueue) override;
    std::string GetName() override;

private:
    CombatActor* m_Owner = nullptr;
    CombatActor* m_Target = nullptr;
    CombatScreen* m_Screen;
    float m_CountDown;
    bool m_IsFinished = false;

    float m_Elapsed = 5.0F;
    int m_FlashCount = 0;
    bool m_Switch = false;
    int m_Phase = 0;
};

#endif
