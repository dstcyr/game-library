//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "graphics/SDLGraphics.h"
#include "inputs/SDLInputs.h"
#include "audio/SDLAudio.h"
#include "resources/PakResources.h"
#include "logs/OutputLogger.h"
#include "logs/FileLogger.h"
#include "save/SaveGame.h"
#include "scenes/GameWorld.h"
#include "gui/UINode.h"

Game& Game::Get()
{
    static Game Instance;
    return Instance;
}

bool Game::Initialize(const std::string& title, int width, int height)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    if (IsDebuggerPresent() == TRUE)
    {
        m_LoggerInstance = new OutputLogger();
        m_LoggerInstance->SetLevel(ELogLevel::Log);
    }
    else
    {
        m_LoggerInstance = new FileLogger();
        m_LoggerInstance->SetLevel(ELogLevel::Warning);
    }

    std::string tinyxmlVersion = std::to_string(TINYXML2_MAJOR_VERSION) + "." + std::to_string(TINYXML2_MINOR_VERSION) + "." + std::to_string(TINYXML2_PATCH_VERSION);
    BX_LOG(ELogLevel::Log, "TinyXml2 " + tinyxmlVersion);

    m_GraphicsInstance = new SDLGraphics();
    if (!m_GraphicsInstance->Initialize(title, width, height))
    {
        return false;
    }

    m_AudioInstance = new SdlAudio();
    if (!m_AudioInstance->Initialize())
    {
        return false;
    }

    m_InputsInstance = new SdlInputs();
    m_ResourceInstance = new PakResources("game.pak");

    m_SaveInstance = new SaveGame();

    m_WorldInstance = new GameWorld();

    m_IsRunning = true;
    return true;
}

void Game::Start(const std::string& firstState)
{
    m_WorldInstance->FadeToState(firstState, true);

    clock_t lastTime = clock();
    const int frameDuration = 8;
    float dt = 0.0F;

    while (m_IsRunning)
    {
        const clock_t startTime = clock();

        dt = (startTime - lastTime) * 0.001F;
        ProcessInput(dt);
        Update(dt);
        UpdateUI(dt);

        m_GraphicsInstance->Clear();
        Draw();
        DrawUI();
        m_GraphicsInstance->Present();

        int restTime = startTime + frameDuration - clock();
        if (restTime > 0)
        {
            Sleep(restTime);
        }

        lastTime = startTime;
    }

    Destroy();
}

void Game::QuitGame()
{
    m_IsRunning = false;
}

void Game::PushUINode(UINode* node)
{
    m_UIStack.PushBack(node);
}

void Game::FlushUIStack()
{
    while (!m_UIStack.IsEmpty())
    {
        UINode* node = m_UIStack.PopBack();
        m_UIStackToDelete.PushBack(node);
    }
}

void Game::PopUINode()
{
    if (!m_UIStack.IsEmpty())
    {
        UINode* node = m_UIStack.PopBack();
        m_UIStackToDelete.PushBack(node);
    }
}

void Game::ProcessInput(float dt)
{
    m_InputsInstance->Update();

    for (auto it = m_UIStack.Begin(); it != m_UIStack.End(); it++)
    {
        if (!(*it)->ProcessInput(dt))
        {
            return;
        }
    }

    if (!m_WorldInstance->ProcessInput(dt))
    {
        return;
    }

#if defined(_DEBUG)
    // if (m_InputsInstance->IsKeyPressed(EKey::EKEY_ESCAPE))
    // {
    //     QuitGame();
    // }
#endif
}

void Game::Update(float dt)
{
    m_WorldInstance->Update(dt);
}

void Game::UpdateUI(float dt)
{
    if (!m_UIStack.IsEmpty())
    {
        UINode* top = m_UIStack.Last();
        BX_CHECKS(top != nullptr, "Top ui node is null");

        top->Update(dt);
    }

    while (!m_UIStackToDelete.IsEmpty())
    {
        UINode* node = m_UIStackToDelete.PopBack();
        delete node;
    }
}

void Game::Draw()
{
    m_WorldInstance->Draw();
}

void Game::DrawUI()
{
    m_GraphicsInstance->EnableCamera(false);
    
    for (auto it = m_UIStack.Begin(); it != m_UIStack.End(); it++)
    {
        (*it)->Draw();
    }

    m_GraphicsInstance->EnableCamera(true);
}

void Game::Destroy()
{
    if (m_WorldInstance != nullptr)
    {
        m_WorldInstance->Shutdown();
        delete m_WorldInstance;
        m_WorldInstance = nullptr;
    }

    if (m_SaveInstance != nullptr)
    {
        delete m_SaveInstance;
        m_SaveInstance = nullptr;
    }

    if (m_ResourceInstance != nullptr)
    {
        delete m_ResourceInstance;
        m_ResourceInstance = nullptr;
    }

    if (m_InputsInstance != nullptr)
    {
        delete m_InputsInstance;
        m_InputsInstance = nullptr;
    }

    if (m_AudioInstance != nullptr)
    {
        m_AudioInstance->Shutdown();
        delete m_AudioInstance;
        m_AudioInstance = nullptr;
    }

    if (m_GraphicsInstance != nullptr)
    {
        m_GraphicsInstance->Shutdown();
        delete m_GraphicsInstance;
        m_GraphicsInstance = nullptr;
    }

    if (m_LoggerInstance != nullptr)
    {
        delete m_LoggerInstance;
        m_LoggerInstance = nullptr;
    }
}
