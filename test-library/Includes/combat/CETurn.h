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

#ifndef COMBAT_CETURN_H
#define COMBAT_CETURN_H

#include "ICombatEvent.h"

class CombatScreen;
class CombatActor;

class CETurn : public ICombatEvent
{
public:
    CETurn();
    CETurn(CombatActor* owner, bool isParty, CombatScreen* screen);

    void Execute(CombatEventQueue* eventQueue) override;
    void Update(float deltaTime) override;
    bool IsFinished() override;
    float GetCountDown() const override;
    void SetCountDown(float countdown) override;
    float GetTimePoints(CombatEventQueue* eventQueue) override;
    std::string GetName() override;

private:
    float m_CountDown = 0;
    bool m_IsFinished = false;
    bool m_IsParty = false;
    CombatScreen* m_Screen;
    CombatActor* m_Owner;
};

#endif
