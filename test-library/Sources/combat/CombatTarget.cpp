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
#include "combat/CombatTarget.h"
#include "screens/CombatScreen.h"
#include "combat/CombatActor.h"
#include "scenes/Character.h"
#include "combat/CEAttack.h"

CombatTarget::CombatTarget() :
    CombatTarget(nullptr, nullptr)
{
}

CombatTarget::CombatTarget(CombatScreen* screen, CombatActor* actor) :
    m_Screen(screen),
    m_Actor(actor)
{
}

void CombatTarget::Enter()
{
    m_Icons.Load("textures/inventory_icons.png");
    m_Icons.AddFrame("downarrow", 36, 36, 36, 36);
    m_SelectionLocation = { 0.0F, 0.0F };

    m_Targets.clear();
    bool bIsParty = m_Screen->IsActorInParty(m_Actor);
    if (bIsParty)
    {
        m_Screen->GetEnemyTarget(m_Targets);
    }
    else
    {
        m_Screen->GetPlayerTarget(m_Targets);
    }

    m_SelectedIndex = 0;
    if (m_Targets.empty())
    {
        m_IsFinished = true;
        return;
    }

    if (m_Screen->IsGameOver())
    {
        m_IsFinished = true;
    }

    SelectTarget(m_Targets[m_SelectedIndex]);

    m_Actor->character->SetAnimationFrame("prone");
    m_IsFinished = false;
}

bool CombatTarget::ProcessInput(float deltaTime)
{
    IInputs& tInput = Game::Get().Inputs();
    int len = static_cast<int>(m_Targets.size());

    if (tInput.IsKeyPressed(EKey::EKEY_UP))
    {
        m_SelectedIndex--;
        if (m_SelectedIndex < 0)
        {
            m_SelectedIndex = len - 1;
        }

        SelectTarget(m_Targets[m_SelectedIndex]);
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_DOWN))
    {
        m_SelectedIndex++;
        if (m_SelectedIndex > len - 1)
        {
            m_SelectedIndex = 0;
        }

        SelectTarget(m_Targets[m_SelectedIndex]);
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_RETURN))
    {
        ICombatEvent* attackEvent = new CEAttack(m_Actor, m_Targets[m_SelectedIndex], m_Screen);
        auto* eventQueue = m_Screen->GetEventQueue();
        float tp = attackEvent->GetTimePoints(eventQueue);
        eventQueue->Add(attackEvent, tp);

#if defined(DEBUG_COMBAT)
        BX_LOG(ELogLevel::Log, m_Actor->GetName() + " targets " + m_Targets[m_SelectedIndex]->GetName());
#endif

        m_Screen->HideSelection();
        m_IsFinished = true;
    }

    return true;
}

void CombatTarget::Update(float deltaTime)
{
}

void CombatTarget::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Icons.Draw("downarrow", m_SelectionLocation.first, m_SelectionLocation.second);
}

bool CombatTarget::IsFinished()
{
    return m_IsFinished;
}

void CombatTarget::SelectTarget(CombatActor* target)
{
    int tIndex = -1;
    for (CombatActor* actor : m_Targets)
    {
        tIndex++;
        if (actor == target)
        {
            bool bIsParty = m_Screen->IsActorInParty(actor);
            float wx = 0.0F;
            float wy = 0.0F;

            actor->character->SetSelectPadding(35.0F);
            actor->character->GetSelectPosition(&wx, &wy, 36.0F, 36.0F);
            m_SelectionLocation = { wx, wy };
        }
    }
}
