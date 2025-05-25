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

#ifndef COMBAT_COMBATEVENTQUEUE_H
#define COMBAT_COMBATEVENTQUEUE_H

class ICombatEvent;

class CombatEventQueue
{
public:
    static float GetTimePointsFromSpeed(float speed);
    void Add(ICombatEvent* ce, float timePoints);
    void Clear();
    bool IsEmpty();
    void Print();
    void Update(float deltaTime);

    auto Begin() { return m_Queue.Begin(); }
    auto End() { return m_Queue.End(); }
    ICombatEvent* GetCurrent() { return m_CurrentEvent; }

private:
    TArray<ICombatEvent> m_Queue;
    ICombatEvent* m_CurrentEvent = nullptr;
};

#endif
