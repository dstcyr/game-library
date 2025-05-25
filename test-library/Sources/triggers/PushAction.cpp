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
#include "triggers/PushAction.h"
#include "scenes/Character.h"
#include "triggers/Trigger.h"
#include "properties/MapPropertyCollection.h"
#include "maps/TileMap.h"

Trigger* PushAction::Create(const MapPropertyCollection& definition, Tilemap* map)
{
    auto* trigger = new Trigger();
    int tileX = definition.GetInt("TargetX");
    int tileY = definition.GetInt("TargetY");
    std::string mapName = definition.GetString("Map");

    auto* pushAction = new PushAction(mapName, tileX, tileY);
    pushAction->Initialize();
    trigger->SetOnEnterAction(pushAction);

    return trigger;
}

PushAction::PushAction(std::string mapName, int mapX, int mapY) :
    m_MapName(std::move(mapName)), m_TargetX(mapX), m_TargetY(mapY)
{
}

void PushAction::Initialize()
{
}

void PushAction::Execute(Entity* entity)
{
    m_EntityPtr = entity;
    Game::Get().World().FadeOut(std::bind(&PushAction::FadeOutComplete, this));
}

void PushAction::FadeOutComplete()
{
    IWorld& tWorld = Game::Get().World();
    m_EntityPtr->SetLocalLocation(m_TargetX, m_TargetY);
    Game::Get().World().PushState(m_MapName);

    Game::Get().World().FadeIn();
}
