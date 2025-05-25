//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/ExploreState.h"
#include "scenes/Character.h"
#include "../../test-library/Includes/Scenes/Chest.h"
#include "../../test-library/Includes/triggers/TeleportAction.h"
#include "../../test-library/Includes/triggers/WarpAction.h"
#include "../../test-library/Includes/triggers/PushAction.h"
#include "../../test-library/Includes/triggers/PopAction.h"

StoryState* ExploreState::Create(Storyboard* screen, const std::string& id, const std::string& map)
{
    StoryState* state = new ExploreState(screen, id, map);
    state->Enter();
    return state;
}

ExploreState::ExploreState(Storyboard* screen, const std::string& id, const std::string& map) :
    StoryState(screen, id, 0, 0, 0, 0), m_MapName(map)
{
    m_IsReady = false;
}

void ExploreState::Enter()
{
    if (!m_MapName.empty())
    {
        IGraphics& tGraphics = Game::Get().Graphics();
        IWorld& tWorld = Game::Get().World();

        m_Map = new Tilemap();
        m_Map->RegisterEntityFactory("Chest", &Chest::Create);
        m_Map->RegisterEntityFactory("Character", &Character::Create);
        m_Map->RegisterTriggerFactory("Teleport", &TeleportAction::Create);
        m_Map->RegisterTriggerFactory("Warp", &WarpAction::Create);
        m_Map->RegisterTriggerFactory("Push", &PushAction::Create);
        m_Map->RegisterTriggerFactory("Pop", &PopAction::Create);

        if (m_Map->LoadMap(m_MapName))
        {
            m_Camera = tWorld.GetCamera();
            m_Camera->SetParentMap(m_Map);
            m_Camera->Focus(100.0F, 100.0F);
            
            // TODO (DaSt):
            // m_Screen->AddMap(m_Map);
        }
    }

    m_IsReady = true;
}

void ExploreState::Exit()
{
    // TODO (DaSt):
    // m_Screen->RemoveMap(m_Map);
}

void ExploreState::Update(float dt)
{
}

bool ExploreState::ProcessInput(float dt)
{
    return false;
}

void ExploreState::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    tGraphics.EnableCamera(false);
    tGraphics.FillRect(0.0F, 0.0F, 2000.0F, 2000.0F, 0, 0, 0, 255);
    tGraphics.EnableCamera(true);

    if (m_Map != nullptr)
    {
        m_Map->Draw();
    }
}
