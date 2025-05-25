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
#include "triggers/TeleportAction.h"
#include "maps/Tilemap.h"
#include "triggers/Trigger.h"
#include "properties/MapPropertyCollection.h"

Trigger* TeleportAction::Create(const MapPropertyCollection& definition, Tilemap* map)
{
    auto* trigger = new Trigger();
    int tileX = definition.GetInt("TargetX");
    int tileY = definition.GetInt("TargetY");

    auto* teleportAction = new TeleportAction(tileX, tileY);
    teleportAction->Initialize();
    trigger->SetOnEnterAction(teleportAction);

    return trigger;
}

TeleportAction::TeleportAction(int tileX, int tileY) :
    m_TargetX(tileX),
    m_TargetY(tileY)
{
}

void TeleportAction::Initialize()
{
    IAudio& tAudio = Game::Get().Audio();
    m_TeleportSFX = tAudio.LoadAudio("sounds/reveal.ogg");
}

void TeleportAction::Execute(Entity* entity)
{
    m_EntityPtr = entity;

    if (m_TeleportSFX > 0)
    {
        IAudio& tAudio = Game::Get().Audio();
        tAudio.PlayAudio(m_TeleportSFX, 0);
    }

    Game::Get().World().FadeOut(std::bind(&TeleportAction::FadeOutComplete, this));
}

void TeleportAction::FadeOutComplete()
{
    if (m_EntityPtr != nullptr)
    {
        IWorld& tWorld = Game::Get().World();
        float eW = 0.0F;
        float eH = 0.0F;
        float worldX = 0.0F;
        float worldY = 0.0F;
        m_EntityPtr->GetSize(&eW, &eH);

        Tilemap* map = m_EntityPtr->GetParentMap();

        map->GetTransform().GetTileFoot(m_TargetX, m_TargetY, &worldX, &worldY, eW, eH);
        m_EntityPtr->SetLocalLocation(m_TargetX, m_TargetY);
        m_EntityPtr->SetWorldLocation(worldX, worldY);
    }

    Game::Get().World().FadeIn();
}
