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
#include "combat/CEEnemyDie.h"
#include "maths/Tween.h"
#include "scenes/Character.h"
#include "combat/CombatActor.h"
#include "combat/CombatEventQueue.h"
#include "stats/CharacterDefinition.h"

CEEnemyDie::CEEnemyDie() :
    CEEnemyDie(nullptr, nullptr)
{
}

CEEnemyDie::CEEnemyDie(CombatActor* owner, CombatScreen* screen) :
    m_Actor(owner), m_Screen(screen), m_Queue(nullptr)
{
}

void CEEnemyDie::Execute(CombatEventQueue* eventQueue)
{
    m_IsFinished = false;
    m_Elapsed = 0.0F;
    m_Duration = 0.2F;
    m_Queue = eventQueue;

#if defined(DEBUG_COMBAT)
    BX_LOG(ELogLevel::Log, m_Actor->GetName() + " dies");
#endif

    IAudio& tAudio = Game::Get().Audio();
    size_t sfx = tAudio.LoadAudio("sounds/smallEsplosion.wav");
    tAudio.PlaySFX(sfx);
}

void CEEnemyDie::Update(float deltaTime)
{
    m_Elapsed += deltaTime;
    float alpha = Tween::Linear(m_Elapsed, 255, 0, m_Duration);
    m_Actor->character->SetColor(255, 255, 255, static_cast<unsigned char>(alpha));

    if (MathUtils::NearEqual(alpha, 0.0F))
    {
        m_IsFinished = true;
    }
}

bool CEEnemyDie::IsFinished()
{
    return m_IsFinished;
}

float CEEnemyDie::GetCountDown() const
{
    return -1.0F;
}

void CEEnemyDie::SetCountDown(float countdown)
{
}

float CEEnemyDie::GetTimePoints(CombatEventQueue* eventQueue)
{
    if (m_Actor != nullptr)
    {
        float speed = m_Actor->definition->attributes.GetSpeedAttribute().GetValue();
        return CombatEventQueue::GetTimePointsFromSpeed(speed);
    }

    return -1.0F;
}

std::string CEEnemyDie::GetName()
{
    return std::string("ENEMY DIE -> ") + m_Actor->character->GetName();
}
