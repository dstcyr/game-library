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
#include "combat/CombatMove.h"
#include "combat/CombatActor.h"
#include "scenes/Character.h"
#include "maths/Tween.h"
#include "stats/AttributeSet.h"
#include "combat/CEEnemyDie.h"
#include "screens/CombatScreen.h"
#include "combat/EnemyHurt.h"
#include "effects/FloatingNumber.h"
#include "effects/Slash.h"

CombatMove::CombatMove() :
    CombatMove(nullptr, nullptr, nullptr)
{
}

CombatMove::CombatMove(CombatScreen* screen, CombatActor* actor, CombatActor* target) :
    m_Screen(screen),
    m_Actor(actor),
    m_Target(target)
{
}

void CombatMove::Enter()
{
    m_Actor->character->GetWorldLocation(&m_OriginalX, &m_OriginalY);
    m_DestinationX = m_OriginalX - 100.0F;
    m_Elapsed = 0.0F;
    m_Duration = 0.3F;
    m_Phase = 0;
    m_IsFinished = false;

    if (m_Screen->IsGameOver())
    {
        m_IsFinished = true;
        return;
    }

    if (m_Actor->IsDead() || m_Screen->IsGameOver())
    {
        m_Phase = 6;
    }
}

bool CombatMove::ProcessInput(float deltaTime)
{
    return false;
}

void CombatMove::Update(float deltaTime)
{
    if (m_Phase == 0 || m_Phase == 4)
    {
        m_Actor->character->PlayAnimation("standby", true);
        m_Phase++;
    }
    else if(m_Phase == 1)
    {
        m_Elapsed += deltaTime;

        float newX = Tween::Linear(m_Elapsed, m_OriginalX, m_DestinationX, m_Duration);
        m_Actor->character->SetWorldLocation(newX, m_OriginalY);

        if (m_Elapsed >= m_Duration)
        {
            m_Elapsed = 0.0F;
            m_Phase++;
        }
    }
    else if (m_Phase == 2)
    {
        m_Actor->character->PlayAnimationOnce("attack", [this]() {
            DoAttack();
            m_Phase++;
            }
        );

        m_Phase++;
    }
    else if (m_Phase == 5)
    {
        m_Elapsed += deltaTime;

        float newX = Tween::Linear(m_Elapsed, m_DestinationX, m_OriginalX, m_Duration);
        m_Actor->character->SetWorldLocation(newX, m_OriginalY);

        if (m_Elapsed >= m_Duration)
        {
            m_Elapsed = 0.0F;
            m_Phase++;
        }
    }
    else if (m_Phase == 6)
    {
        m_IsFinished = true;
    }
}

void CombatMove::Draw()
{
}

bool CombatMove::IsFinished()
{
    return m_IsFinished;
}

void CombatMove::DoAttack()
{
    if (m_Target->IsDead())
    {
        m_Target = m_Screen->GetRandomEnemyMember();
    }

    if (m_Target != nullptr)
    {
        // TODO(DaSt) : hard code attack to 10 for now, no defense
        //      attack = attack + strength
        //      damage = attack - defense

#if defined(DEBUG_COMBAT)
        BX_LOG(ELogLevel::Log, m_Actor->GetName() + " attacks " + m_Target->GetName());
#endif

        float damage = 10.0F;
        m_Target->definition->TakeDamage(damage);

        m_Screen->AddEffect(FloatingNumber::Create(m_Target->character, static_cast<int>(damage)));
        m_Screen->AddEffect(Slash::Create(m_Target->character));

        auto* state = new EnemyHurt(m_Screen, m_Actor, m_Target);
        state->Enter();
        m_Screen->Push(state);

        if (m_Target->IsDead())
        {
            m_Screen->GetEventQueue()->Add(new CEEnemyDie(m_Target, m_Screen), -1.0F);
        }
        else
        {

        }
    }
}
