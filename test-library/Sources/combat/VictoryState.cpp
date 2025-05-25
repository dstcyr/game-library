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
#include "combat/VictoryState.h"
#include "screens/CombatScreen.h"
#include "combat/CombatActor.h"
#include "scenes/Character.h"

VictoryState::VictoryState() :
    VictoryState(nullptr)
{

}

VictoryState::VictoryState(CombatScreen* screen) :
    m_Screen(screen)
{

}

void VictoryState::Enter()
{
    bool bPartyWins = m_Screen->PartyWins();
    bool bEnemyWins = m_Screen->EnemyWins();
    BX_CHECKS(bPartyWins || bEnemyWins, "Victory called but no party won the battle");

    if (bPartyWins)
    {
        m_Screen->PlayVictoryFanfare();
        m_Screen->ShowNotification("You are victorious!");
        std::vector<CombatActor*> party;
        m_Screen->GetParty(party);

        for (auto* actor : party)
        {
            actor->character->PlayAnimation("victory", true);
        }
    }
    else
    {
        m_Screen->PlayDefeatSong();
        m_Screen->ShowNotification("The party has perished...");
    }

    m_Elapsed = 0.0F;
    m_Delay = 3.0F;
}

bool VictoryState::ProcessInput(float deltaTime)
{
    return true;
}

void VictoryState::Update(float deltaTime)
{
    m_Elapsed += deltaTime;
    if (m_Elapsed >= m_Delay)
    {
        m_Elapsed = 0.0F;
        IWorld& tWorld = Game::Get().World();

        bool bPartyWins = m_Screen->PartyWins();

        if (bPartyWins)
        {
            tWorld.PopState();
        }
        else
        {
            tWorld.FadeToState("MainMenu", true);
        }
    }
}

void VictoryState::Draw()
{
}

bool VictoryState::IsFinished()
{
    return false;
}
