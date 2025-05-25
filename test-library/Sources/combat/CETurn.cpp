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
#include "combat/CETurn.h"
#include "combat/CEAttack.h"
#include "combat/CombatEventQueue.h"
#include "gui/UIChoice.h"
#include "screens/CombatScreen.h"
#include "scenes/Character.h"
#include "combat/CombatActor.h"
#include "combat/CombatTarget.h"
#include "combat/CombatHurt.h"
#include "effects/FloatingNumber.h"
#include "effects/Claw.h"

CETurn::CETurn() : CETurn(nullptr, false, nullptr) {}
CETurn::CETurn(CombatActor* owner, bool isParty, CombatScreen* screen) :
    m_Owner(owner), m_IsParty(isParty), m_Screen(screen)
{
}

void CETurn::Execute(CombatEventQueue* eventQueue)
{
    if (m_Screen->IsGameOver())
    {
        m_IsFinished = true;
        return;
    }

    if (m_Owner->IsDead())
    {
        m_IsFinished = true;
        return;
    }

    if (m_IsParty)
    {
        if (m_Owner != nullptr)
        {
            m_Screen->SelectCharacter(m_Owner);
            std::vector<std::string> dataSource;
            dataSource.emplace_back("Attack");

            UIChoice::Create("Combat Menu", dataSource, 300.0F, 850.0F, [this, eventQueue](int option) {

                if (option == 0)
                {
                    auto* state = new CombatTarget(m_Screen, m_Owner);
                    state->Enter();
                    m_Screen->Push(state);
                }

                m_IsFinished = true;
                }
            );
        }
    }
    else
    {
        CombatActor* randomCharacter = m_Screen->GetRandomPartyMember();
        if (!randomCharacter->IsDead())
        {
            ICombatEvent* attackEvent = new CEAttack(m_Owner, randomCharacter, m_Screen);
            auto* eventQueue = m_Screen->GetEventQueue();
            float tp = attackEvent->GetTimePoints(eventQueue);
            eventQueue->Add(attackEvent, tp);

#if defined(DEBUG_COMBAT)
            BX_LOG(ELogLevel::Log, m_Owner->GetName() + " targets " + randomCharacter->GetName());
#endif
        }

        m_IsFinished = true;
    }
}

void CETurn::Update(float deltaTime)
{
}

bool CETurn::IsFinished()
{
    return m_IsFinished;
}

float CETurn::GetCountDown() const
{
    return m_CountDown;
}

void CETurn::SetCountDown(float countdown)
{
    m_CountDown = countdown;
}

float CETurn::GetTimePoints(CombatEventQueue* eventQueue)
{
    if (m_Owner != nullptr)
    {
        float speed = m_Owner->definition->attributes.GetSpeedAttribute().GetValue();
        return CombatEventQueue::GetTimePointsFromSpeed(speed);
    }

    return -1.0F;
}

std::string CETurn::GetName()
{
    return std::string("TURN -> ") + m_Owner->character->GetName();
}