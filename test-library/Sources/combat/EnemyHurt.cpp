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
#include "combat/EnemyHurt.h"
#include "screens/CombatScreen.h"
#include "combat/CombatActor.h"
#include "scenes/Character.h"
#include "maths/Tween.h"

EnemyHurt::EnemyHurt():
    EnemyHurt(nullptr, nullptr, nullptr)
{
}

EnemyHurt::EnemyHurt(CombatScreen* screen, CombatActor* actor, CombatActor* target) :
    m_Screen(screen),
    m_Actor(actor),
    m_Target(target)
{
}

void EnemyHurt::Enter()
{
    m_IsFinished = false;
    m_Duration = 0.05F;
    m_Target->character->GetWorldLocation(&m_OriginalX, &m_OriginalY);
    m_Target->character->SetWorldLocation(m_OriginalX - 5.0F, m_OriginalY);
    m_Target->character->SetColor(255, 255, 0, 255);
}

bool EnemyHurt::ProcessInput(float deltaTime)
{
    return false;
}

void EnemyHurt::Update(float deltaTime)
{
    m_Elapsed += deltaTime;
    if (m_Elapsed > m_Duration)
    {
        m_Target->character->SetWorldLocation(m_OriginalX, m_OriginalY);
        m_Target->character->SetColor(255, 255, 255, 255);
        m_IsFinished = true;
    }
}

void EnemyHurt::Draw()
{
}

bool EnemyHurt::IsFinished()
{
    return m_IsFinished;
}
