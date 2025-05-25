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

#ifndef COMBAT_ICOMBATEVENT_H
#define COMBAT_ICOMBATEVENT_H

#include <string>

class ICombatEvent
{
public:
    virtual ~ICombatEvent() = default;
    virtual void Execute(class CombatEventQueue* eventQueue) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual bool IsFinished() = 0;

    virtual void SetCountDown(float countdown) = 0;
    virtual float GetCountDown() const = 0;
    virtual float GetTimePoints(CombatEventQueue* eventQueue) = 0;
    virtual std::string GetName() = 0;
};

#endif
