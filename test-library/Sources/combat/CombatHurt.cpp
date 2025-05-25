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
#include "combat/CombatHurt.h"
#include "screens/CombatScreen.h"
#include "combat/CombatActor.h"
#include "scenes/Character.h"

CombatHurt::CombatHurt() :
    CombatHurt(nullptr, nullptr, nullptr)
{
}

CombatHurt::CombatHurt(CombatScreen* screen, CombatActor* actor, CombatActor* target) :
    m_Screen(screen),
    m_Actor(actor),
    m_Target(target)
{
}

void CombatHurt::Enter()
{
    m_IsFinished = false;
    if (m_Target != nullptr)
    {
        auto* character = m_Target->character;
        if (character != nullptr)
        {
            m_PreviousClip = character->GetCurrentClipName();
            m_Loop = character->IsLooping();
            m_Elapsed = 0.0F;
            m_Duration = 1.0F;

            character->PlayAnimationOnce("hurt", [this]()
                {
                    m_AnimationCompleted = true;
                    m_Target->character->PlayAnimation(m_PreviousClip, m_Loop);
                });
        }
    }
}

bool CombatHurt::ProcessInput(float deltaTime)
{
    return true;
}

void CombatHurt::Update(float deltaTime)
{
    if (m_AnimationCompleted)
    {
        m_Elapsed += deltaTime;
        if (m_Elapsed >= m_Duration)
        {
            m_IsFinished = true;
        }
    }
}

void CombatHurt::Draw()
{
}

bool CombatHurt::IsFinished()
{
    return m_IsFinished;
}
