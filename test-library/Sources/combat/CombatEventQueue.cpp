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

#include "Config.h"
#include "combat/CombatEventQueue.h"
#include "combat/ICombatEvent.h"

float CombatEventQueue::GetTimePointsFromSpeed(float speed)
{
    float maxSpeed = 255.0F;
    speed = MathUtils::Min(speed, maxSpeed);

    float points = maxSpeed - speed;
    return std::floor(points);
}

void CombatEventQueue::Add(ICombatEvent* ce, float timePoints)
{
    if (timePoints < 0.0F)
    {
        ce->SetCountDown(-1.0F);
    }
    else
    {
        ce->SetCountDown(timePoints);
    }

    m_Queue.PushBack(ce);
    m_Queue.Sort([](const ICombatEvent* a, const ICombatEvent* b)
        {
            return a->GetCountDown() < b->GetCountDown();
        }
    );
}

void CombatEventQueue::Clear()
{
    while (!m_Queue.IsEmpty())
    {
        ICombatEvent* ce = m_Queue.PopBack();
        delete ce;
    }

    if (m_CurrentEvent != nullptr)
    {
        delete m_CurrentEvent;
        m_CurrentEvent = nullptr;
    }
}

bool CombatEventQueue::IsEmpty()
{
    return m_Queue.IsEmpty();
}

void CombatEventQueue::Print()
{
    ILogger& tLogger = Game::Get().Logger();
    if (IsEmpty())
    {
        tLogger.Add("Event Queue is empty");
        return;
    }

    tLogger.Add("Event Queue: ");
    if (m_CurrentEvent != nullptr)
    {
        tLogger.Add("Current Event: " + m_CurrentEvent->GetName());
    }
    else
    {
        tLogger.Add("Current Event: null");
    }

    int cnt = 1;
    for (auto it = m_Queue.Begin(); it != m_Queue.End(); it++)
    {
        tLogger.Add("[" + std::to_string(cnt) + "] Event: [" + std::to_string((*it)->GetCountDown()) + "][" + (*it)->GetName() + "]");
        cnt++;
    }
}

void CombatEventQueue::Update(float deltaTime)
{
    if (m_CurrentEvent != nullptr)
    {
        m_CurrentEvent->Update(deltaTime);
        if (m_CurrentEvent->IsFinished())
        {
            delete m_CurrentEvent;
            m_CurrentEvent = nullptr;
        }
        else
        {
            return;
        }
    }
    else if (IsEmpty())
    {
        return;
    }
    else
    {
        ICombatEvent* front = m_Queue.PopFront();
        front->Execute(this);
        m_CurrentEvent = front;
    }

    for (auto it = m_Queue.Begin(); it != m_Queue.End(); it++)
    {
        float cd = (*it)->GetCountDown();
        cd = MathUtils::Max(0.0F, cd - 1.0F);
        (*it)->SetCountDown(cd);
    }
}
