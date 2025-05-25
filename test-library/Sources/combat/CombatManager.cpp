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
#include "combat/CombatManager.h"

ICombat& CombatManager::Get()
{
    static CombatManager combat;
    return combat;
}

void CombatManager::Initialize()
{
    m_BackgroundMap.emplace("Cave", "textures/combat_bg_cave.png");
    m_BackgroundMap.emplace("Grass", "textures/Battle Backgrounds3.png");
    m_BackgroundMap.emplace("Forest", "textures/Battle Backgrounds1.png");
    m_BackgroundMap.emplace("Room", "textures/combat_bg_town.png");
    m_BackgroundMap.emplace("Town", "textures/Battle Backgrounds19.png");
    m_BackgroundMap.emplace("Ruin", "textures/Battle Backgrounds15.png");
    m_BackgroundMap.emplace("Castle", "textures/Battle Backgrounds13.png");
    m_BackgroundMap.emplace("Desert", "textures/Battle Backgrounds8.png");
}

void CombatManager::StartCombat()
{
    IWorld& tWorld = Game::Get().World();
    FStateInfo stateInfo = tWorld.GetStateInfo();

    if (stateInfo.hasInfo)
    {
        std::string backgroundImagePath;
        if (m_BackgroundMap.count(stateInfo.tileType) > 0)
        {
            backgroundImagePath = m_BackgroundMap[stateInfo.tileType];
        }
        else
        {
            backgroundImagePath = "textures/nobg.png";
        }

        IGraphics& tGraphics = Game::Get().Graphics();
        m_BackgroundImage = tGraphics.LoadTexture(backgroundImagePath);

        if (stateInfo.isTopState)
        {
            tWorld.PushState("Combat");
        }
        else
        {
            tWorld.ReplaceState("Combat");
        }
    }
}
