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
#include "triggers/PopAction.h"
#include "scenes/Character.h"
#include "maps/Tilemap.h"
#include "triggers/Trigger.h"
#include "properties/MapPropertyCollection.h"

Trigger* PopAction::Create(const MapPropertyCollection& definition, Tilemap* map)
{
    auto* trigger = new Trigger();
    int tileX = definition.GetInt("TargetX");
    int tileY = definition.GetInt("TargetY");

    auto* popAction = new PopAction(tileX, tileY);
    popAction->Initialize();
    trigger->SetOnEnterAction(popAction);

    return trigger;
}

PopAction::PopAction(int mapX, int mapY) :
    m_TargetX(mapX), m_TargetY(mapY)
{
}

void PopAction::Initialize()
{
}

void PopAction::Execute(Entity* entity)
{
    m_EntityPtr = entity;
    Game::Get().World().FadeOut(std::bind(&PopAction::FadeOutComplete, this));
}

void PopAction::FadeOutComplete()
{
    IWorld& tWorld = Game::Get().World();
    m_EntityPtr->SetLocalLocation(m_TargetX, m_TargetY);

    float wX = 0.0F;
    float wY = 0.0F;
    Tilemap* map = m_EntityPtr->GetParentMap();
    if (map != nullptr)
    {
        map->GetTransform().GetTileFoot(m_TargetX, m_TargetY, &wX, &wY, 32, 48);
        m_EntityPtr->SetWorldLocation(wX, wY);
    }

    Game::Get().World().PopState();

    Game::Get().World().FadeIn();
}
