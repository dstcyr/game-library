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
#include "screens/GameLocationState.h"
#include "scenes/Character.h"
#include "scenes/Camera.h"
#include "maps/Tilemap.h"
#include "gui/UINotification.h"
#include "gui/UIChoice.h"
#include "../../Includes/combat/CombatManager.h"
#include "../../Includes/Scenes/Chest.h"
#include "../../Includes/triggers/TeleportAction.h"
#include "../../Includes/triggers/WarpAction.h"
#include "../../Includes/triggers/PushAction.h"
#include "../../Includes/triggers/PopAction.h"

GameLocationState::GameLocationState(FLevelConfig config) :
    m_LevelConfig(std::move(config))
{
}

void GameLocationState::Enter()
{
    UseMap(m_LevelConfig.mapName);
    UseMusic(m_LevelConfig.themeName);
}

bool GameLocationState::ProcessInput(float deltaTime)
{
    IInputs& tInputs = Game::Get().Inputs();
    IWorld& tWorld = Game::Get().World();

    if (tInputs.IsKeyPressed(EKey::EKEY_ESCAPE))
    {
        tWorld.PushState("GameMenu");
    }

    if (tInputs.IsKeyPressed(EKey::EKEY_F1))
    {
        tWorld.PushState("CheatMenu");
    }

    if (tInputs.IsKeyPressed(EKey::EKEY_F2))
    {
        ICombat& tCombat = CombatManager::Get();
        tCombat.StartCombat();
    }

#if defined(DEBUG_TILE_TYPE)
    if (tInputs.IsKeyPressed(EKey::EKEY_F3))
    {
        if (m_Hero != nullptr)
        {
            int posX = 0;
            int posY = 0;
            m_Hero->GetLocalLocation(&posX, &posY);
            tWorld.GetTileType(posX, posY);
        }
    }
#endif

    if (!m_Map->ProcessInput(deltaTime))
    {
        return false;
    }

    if (!m_Hero->ProcessInput(deltaTime))
    {
        return false;
    }

    if (!m_Camera->ProcessInput(deltaTime))
    {
        return false;
    }

    return true;
}

void GameLocationState::Update(float deltaTime)
{
    m_Map->Update(deltaTime);
    m_Hero->Update(deltaTime);
    m_Camera->Update(deltaTime);
}

void GameLocationState::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    if (m_Map != nullptr)
    {
        m_Map->Draw();
    }

#if defined(DEBUG_MAP_NAMES)
    tGraphics.EnableCamera(false);

    int textW = 0;
    int textH = 0;
    tGraphics.GetTextSize(m_LevelConfig.mapName, m_Font, &textW, &textH);

    float bgW = static_cast<float>(textW) + 10.0F;
    float bgH = static_cast<float>(textH) + 10.0F;
    tGraphics.FillRect(10.0F, 10.0F, bgW, bgH, 0, 0, 0, 255);

    tGraphics.DrawString(m_LevelConfig.mapName, m_Font, 15.0F, 15.0F, 255, 255, 0, 255);
    tGraphics.EnableCamera(true);
#endif
}

void GameLocationState::Exit()
{
    IAudio& tAudio = Game::Get().Audio();
    tAudio.StopAllSounds();
    Destroy();
}

void GameLocationState::Destroy()
{
    if (m_Map != nullptr)
    {
        m_Map->RemoveFromObjectLayer(m_Hero);

        m_Map->Clear();
        delete m_Map;
        m_Map = nullptr;
    }
}

void GameLocationState::Pause()
{
    m_Map->RemoveFromObjectLayer(m_Hero);
}

void GameLocationState::Resume()
{
    m_Map->AddToObjectLayer(m_Hero);
    m_Hero->SetParentMap(m_Map);
    m_Hero->ResumeControls();
    m_Camera->SetParentMap(m_Map);

    if (!m_LevelConfig.themeName.empty())
    {
        IAudio& tAudio = Game::Get().Audio();
        if (!tAudio.IsMusicPlaying())
        {
            tAudio.PlayMusic(m_Theme);
        }
    }
}

FStateInfo GameLocationState::GetStateInfo()
{
    FStateInfo info;
    info.hasInfo = true;
    info.mapName = m_Map->GetName();

    int posX = 0;
    int posY = 0;
    m_Hero->GetLocalLocation(&posX, &posY);

    info.tileType = GetTileType(posX, posY);
    return info;
}

std::string GameLocationState::GetTileType(int x, int y)
{
    if (m_Map != nullptr)
    {
        return m_Map->GetTileType(x, y);
    }

    return "";
}

void GameLocationState::Save(BufferedFile* saveFile)
{
    if (m_Map != nullptr)
    {
        m_Map->Save(saveFile);
    }
}

void GameLocationState::Load(BufferedFile* saveFile)
{
    if (m_Map != nullptr)
    {
        m_Map->Load(saveFile);
    }
}

void GameLocationState::UseMap(const std::string& mapName)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    IWorld& tWorld = Game::Get().World();

    m_Font = tGraphics.LoadFont("fonts/junction.ttf", 28);

    if (!mapName.empty())
    {
        m_Map = new Tilemap();
        m_Map->RegisterEntityFactory("Chest", &Chest::Create);
        m_Map->RegisterEntityFactory("Character", &Character::Create);
        m_Map->RegisterTriggerFactory("Teleport", &TeleportAction::Create);
        m_Map->RegisterTriggerFactory("Warp", &WarpAction::Create);
        m_Map->RegisterTriggerFactory("Push", &PushAction::Create);
        m_Map->RegisterTriggerFactory("Pop", &PopAction::Create);

        if (m_Map->LoadMap(mapName))
        {
            m_Camera = tWorld.GetCamera();
            m_Camera->SetParentMap(m_Map);

            m_Hero = tWorld.GetHero();
            m_Hero->SetParentMap(m_Map);

            int lX = 0;
            int lY = 0;
            m_Hero->GetLocalLocation(&lX, &lY);

            Blackboard* bb = m_Hero->GetBlackboard();
            bb->Reset();

            float wX = 0.0F;
            float wY = 0.0F;
            m_Map->GetTransform().GetTileFoot(lX, lY, &wX, &wY, 32, 48);
            m_Hero->SetWorldLocation(wX, wY);
            m_Map->AddToObjectLayer(m_Hero);

            m_Camera->SetFollow(m_Hero);

            m_Hero->ResumeControls();
        }
    }
}

void GameLocationState::UseMusic(const std::string& themeSong)
{
    if (!themeSong.empty())
    {
        IAudio& tAudio = Game::Get().Audio();
        m_Theme = tAudio.LoadAudio(themeSong);
        tAudio.SetVolume(m_Theme, 50);
        tAudio.PlayMusic(m_Theme);
    }
}
