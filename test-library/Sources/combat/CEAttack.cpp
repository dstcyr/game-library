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
#include "combat/CEAttack.h"
#include "scenes/Character.h"
#include "combat/CombatActor.h"
#include "combat/CombatMove.h"
#include "screens/CombatScreen.h"
#include "effects/FloatingNumber.h"
#include "effects/Claw.h"
#include "combat/CombatHurt.h"

CEAttack::CEAttack() :
    CEAttack(nullptr, nullptr, nullptr)
{
}

CEAttack::CEAttack(CombatActor* owner, CombatActor* target, CombatScreen* screen) :
    m_Owner(owner), m_Target(target), m_Screen(screen), m_CountDown(0)
{
}

void CEAttack::Execute(CombatEventQueue* eventQueue)
{
    if (m_Owner->IsDead())
    {
        m_IsFinished = true;
        return;
    }

    bool isParty = m_Screen->IsActorInParty(m_Owner);
    if (isParty)
    {
        auto* state = new CombatMove(m_Screen, m_Owner, m_Target);
        state->Enter();
        m_Screen->Push(state);

        m_IsFinished = true;
    }

    m_Elapsed = 0.0F;
    m_FlashCount = 0;
    m_Phase = 0;
}

void CEAttack::Update(float deltaTime)
{
    if (m_IsFinished)
    {
        return;
    }


    if (m_Phase == 0)
    {
        m_Elapsed += deltaTime;
        if (m_Elapsed >= 0.5F)
        {
            m_Phase++;
        }
    }
    else if (m_Phase == 1)
    {
        m_Elapsed += deltaTime;
        if (m_Elapsed >= 0.075F)
        {
            m_Elapsed = 0.0F;
            if (m_Switch)
            {
                m_Owner->character->SetColor(150, 150, 150, 255);
            }
            else
            {
                m_Owner->character->SetColor(225, 255, 255, 255);
            }

            m_Switch = !m_Switch;
            m_FlashCount++;

            if (m_FlashCount >= 5)
            {
                m_Phase++;
            }
        }
    }
    else if (m_Phase == 2)
    {
        m_Owner->character->SetColor(225, 255, 255, 255);
        if (m_Target != nullptr)
        {
            float damage = 10.0F;
            m_Target->definition->TakeDamage(damage);

            if (m_Target->IsDead())
            {
                m_Target->character->SetState("combat_die");
            }
            else
            {
                m_Screen->AddEffect(FloatingNumber::Create(m_Target->character, static_cast<int>(damage)));
                m_Screen->AddEffect(Claw::Create(m_Target->character));

                auto* state = new CombatHurt(m_Screen, m_Owner, m_Target);
                state->Enter();
                m_Screen->Push(state);
            }

            m_Screen->UpdateUI();
        }

        m_IsFinished = true;
        m_Phase++;
    }
}

bool CEAttack::IsFinished()
{
    return m_IsFinished;
}

void CEAttack::SetCountDown(float countdown)
{
    m_CountDown = countdown;
}

float CEAttack::GetCountDown() const
{
    return m_CountDown;
}

float CEAttack::GetTimePoints(CombatEventQueue* eventQueue)
{
    if (m_Owner != nullptr)
    {
        float speed = m_Owner->definition->attributes.GetSpeedAttribute().GetValue();
        return CombatEventQueue::GetTimePointsFromSpeed(speed);
    }

    return -1.0F;
}

std::string CEAttack::GetName()
{
    return std::string("ATTACK -> ") + m_Owner->character->GetName();
}