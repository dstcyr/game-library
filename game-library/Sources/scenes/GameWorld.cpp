//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/ObjectLayer.h"
#include "maps/TileLayer.h"
#include "scenes/Character.h"
#include "properties/MapPropertyCollection.h"
#include "scenes/GameWorld.h"
#include "scenes/Camera.h"
#include "triggers/Trigger.h"

void GameWorld::Save(BufferedFile* saveFile)
{
    m_StateMachine.Save(saveFile);
    m_Persistence.Save(saveFile);
    m_StateMachine.SaveState(saveFile);

    if (m_Hero != nullptr)
    {
        m_Hero->Save(saveFile);
    }
}

void GameWorld::Load(BufferedFile* saveFile)
{
    m_StateMachine.Load(saveFile);
    m_Persistence.Load(saveFile);
    m_StateMachine.LoadState(saveFile);

    if (m_Hero != nullptr)
    {
        m_Hero->Load(saveFile);
    }
}

PropertyCollection& GameWorld::GetPersistence()
{
    return m_Persistence;
}

bool GameWorld::ProcessInput(float deltaTime)
{
    return m_StateMachine.ProcessInput(deltaTime);
}

void GameWorld::Update(float deltaTime)
{
    m_StateMachine.Update(deltaTime);
}

void GameWorld::Draw()
{
    m_StateMachine.Draw();
    m_StateMachine.PostDraw();
}

void GameWorld::Shutdown()
{
    m_StateMachine.Clear();

    if (m_Hero != nullptr)
    {
        m_Hero->Clear();
        delete m_Hero;
        m_Hero = nullptr;
    }

    if (m_Camera != nullptr)
    {
        m_Camera->Clear();
        delete m_Camera;
        m_Camera = nullptr;
    }

    m_Persistence.Clear();
}

ControllerState* GameWorld::CreateController(const std::string& name, const std::string& next)
{
    std::string nameUpper = name;
    std::transform(nameUpper.begin(), nameUpper.end(), nameUpper.begin(), ::toupper);

    if (m_ControllerFactories.count(nameUpper) > 0)
    {
        ControllerState* newController = m_ControllerFactories[nameUpper](next);
        return newController;
    }

    return nullptr;
}

void GameWorld::StartNewGame()
{
    // FadeToState("TestCave", false);
    FadeToState("Town", false);
}

Character* GameWorld::GetHero()
{
    std::string name = "Hero";
    size_t instId = Utils::GenerateID(name);

    if (m_Hero == nullptr)
    {
        m_Hero = new Character(instId, name);
        m_Hero->SetSize(32, 48);

        std::string filename = "characters/player.xml";
        m_Hero->Load(filename);
        m_Hero->SetLocalLocation(28, 25);
        //m_Hero->SetLocalLocation(21, 4);
        //m_Hero->SetLocalLocation(17, 14);
    }

    return m_Hero;
}

Camera* GameWorld::GetCamera()
{
    std::string name = "MainCamera";
    size_t instId = Utils::GenerateID(name);

    if (m_Camera == nullptr)
    {
        m_Camera = new Camera(instId, name);
        m_Camera->SetSpeed(0.3F);
    }

    return m_Camera;
}

void GameWorld::FadeToState(const std::string& state, bool startWithBlackScreen)
{
    if (m_Hero != nullptr)
    {
        m_Hero->PauseControls();
    }

    m_StateMachine.FadeTo(state, startWithBlackScreen);
}

void GameWorld::ChangeState(const std::string& state)
{
    if (m_Hero != nullptr)
    {
        m_Hero->PauseControls();
    }

    m_StateMachine.Change(state);
}

void GameWorld::PushState(const std::string& state)
{
    if (m_Hero != nullptr)
    {
        m_Hero->PauseControls();
    }

    m_StateMachine.Push(state);
}

void GameWorld::PopState()
{
    m_StateMachine.Pop();
}

void GameWorld::ReplaceState(const std::string& state)
{
    m_StateMachine.Replace(state);
}

void GameWorld::FadeIn()
{
    m_StateMachine.FadeIn();
}

void GameWorld::FadeOut(const std::function<void()>& callback)
{
    m_StateMachine.FadeOut(callback);
}

FStateInfo GameWorld::GetStateInfo()
{
    return m_StateMachine.GetStateInfo();
}

std::string GameWorld::GetTileType(int x, int y)
{
    return m_StateMachine.GetTileType(x, y);
}

void GameWorld::ClearStates()
{
    m_StateMachine.Clear();
}

void GameWorld::RegisterState(const std::string& name, ScreenState* state)
{
    m_StateMachine.RegisterState(name, state);
}

void GameWorld::RegisterControllerFactory(const std::string& name, TControllerFactory factory)
{
    std::string nameUpper = name;
    std::transform(nameUpper.begin(), nameUpper.end(), nameUpper.begin(), ::toupper);

    if (m_ControllerFactories.count(nameUpper) == 0)
    {
        m_ControllerFactories[nameUpper] = std::move(factory);
    }
}
