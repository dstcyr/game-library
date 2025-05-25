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
#include "screens/tests/TestLogs.h"

void TestLogs::Enter()
{
    BX_LOG(ELogLevel::Log, "TestLogs::Enter");
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);
}

void TestLogs::Update(float deltaTime)
{
    IInputs& tInputs = Game::Get().Inputs();
    if (tInputs.IsKeyPressed(EKey::EKEY_1))
    {
        BX_LOG(ELogLevel::Log, "This is a log");
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_2))
    {
        BX_LOG(ELogLevel::Warning, "This is a warning");
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_3))
    {
        BX_LOG(ELogLevel::Error, "This is an error");
    }

    if (tInputs.IsKeyPressed(EKey::EKEY_ESCAPE))
    {
        Game::Get().QuitGame();
    }
}

void TestLogs::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawString("Test Logs", m_Font, 10.0F, 10.0F, 0, 0, 255, 255);
    tGraphics.DrawString("[1] Write Log", m_Font, 10.0F, 100.0F, 255, 0, 255, 255);
    tGraphics.DrawString("[2] Write Warning", m_Font, 10.0F, 150.0F, 255, 0, 255, 255);
    tGraphics.DrawString("[3] Write Error", m_Font, 10.0F, 200.0F, 255, 0, 255, 255);
    tGraphics.DrawString("[ESC] Quit Game", m_Font, 10.0F, 250.0F, 255, 0, 255, 255);
}
