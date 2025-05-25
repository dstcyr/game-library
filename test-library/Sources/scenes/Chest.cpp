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
#include "scenes/Chest.h"
#include "properties/MapPropertyCollection.h"
#include "triggers/Trigger.h"
#include "save/BufferedFile.h"
#include "inventory/PlayerInventory.h"
#include "maps/Tilemap.h"
#include "gui/UINotification.h"

Entity* Chest::Create(const MapPropertyCollection& definition, Tilemap* map)
{
    const std::string name = definition.GetObjectName();
    const std::string mapName = map->GetName();
    const int idOnTheMap = definition.GetIDOnTheMap();
    size_t instID = Utils::GenerateID(mapName + name, idOnTheMap);

    auto* newChest = new Chest(instID, name);
    newChest->SetParentMap(map);

    float wX = 0.0F;
    float wY = 0.0F;
    int mapX = 0;
    int mapY = 0;
    definition.GetLocalLocation(&mapX, &mapY);

    IWorld& tWorld = Game::Get().World();
    map->GetTransform().GetCenter(mapX, mapY, &wX, &wY, 32.0F, 32.0F);

    newChest->SetWorldLocation(wX, wY);
    newChest->SetLocalLocation(mapX, mapY);
    newChest->Initialize();
    return newChest;
}

Chest::Chest(size_t instId, const std::string& name) :
    Entity(instId, name)
{
    m_UId = std::to_string(instId);
}

void Chest::Initialize()
{
    m_SpriteSheet.Load("textures/chest.png");
    m_SpriteSheet.AddFrame("close", 0, 0, 32, 32);
    m_SpriteSheet.AddFrame("open", 32, 0, 32, 32);

    IWorld& tWorld = Game::Get().World();
    PropertyCollection& tPers = tWorld.GetPersistence();
    m_Open = tPers.GetBool(m_UId);
    m_SpriteSheet.SetFrame(m_Open ? "open" : "close");

    IAudio& tAudio = Game::Get().Audio();
    m_UnlockSFX = tAudio.LoadAudio("sounds/unlock.ogg");
}

void Chest::Load(BufferedFile* saveFile)
{
    IWorld& tWorld = Game::Get().World();
    PropertyCollection& tPers = tWorld.GetPersistence();
    m_Open = tPers.GetBool(m_UId);
    m_SpriteSheet.SetFrame(m_Open ? "open" : "close");
}

void Chest::Draw()
{
    m_SpriteSheet.Draw(m_Bounds.x, m_Bounds.y);
}

void Chest::Draw(float x, float y)
{
    m_SpriteSheet.Draw(m_Bounds.x + x, m_Bounds.y + y);
}

void Chest::Interact()
{
    if (!IsOpen())
    {
        if (m_UnlockSFX > 0)
        {
            IAudio& tAudio = Game::Get().Audio();
            tAudio.PlayAudio(m_UnlockSFX, 0);
        }

        Open();
    }
}

void Chest::Open()
{
    if (!m_Open)
    {
        IInventory& tInventory = PlayerInventory::Get();

        const FItemDefinition& item = FItemDatabase::GetItemDefinition(FItems::SMALL_POTION);
        std::string notifMsg = "Loot " + std::to_string(1) + " " + item.name;
        UINotification::Create(notifMsg, 1.0F);

        m_SpriteSheet.SetFrame("open");
        m_Open = true;

        tInventory.AddItem(FItems::SMALL_POTION, 1);

        IWorld& tWorld = Game::Get().World();
        PropertyCollection& tPers = tWorld.GetPersistence();
        tPers.SetBool(m_UId, m_Open);
    }
}
