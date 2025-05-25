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
#include "screens/tests/TestGameStates.h"

void TestGameStates::Enter()
{
    BX_LOG(ELogLevel::Log, "TestGameStates::Enter");
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);
}

void TestGameStates::Update(float deltaTime)
{
    IInputs& tInputs = Game::Get().Inputs();
    if (tInputs.IsKeyPressed(EKey::EKEY_1))
    {
        for (int i = 0; i < 6; i++)
        {
            BX_LOG(ELogLevel::Log, "i: " + std::to_string(i));

            if (i == 3)
            {
                Game::Get().World().ChangeState("TestChangeStates");
            }
        }
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_2))
    {
        for (int i = 0; i < 6; i++)
        {
            BX_LOG(ELogLevel::Log, "i: " + std::to_string(i));

            if (i == 3)
            {
                Game::Get().World().PushState("TestPushStates");
            }
        }
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_SPACE))
    {
        IWorld& tWorld = Game::Get().World();
        tWorld.StartNewGame();
    }
}

void TestGameStates::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawString("Test Game States", m_Font, 10.0F, 10.0F, 255, 255, 255, 255);
    tGraphics.DrawString("[1] Change state", m_Font, 10.0F, 100.0F, 255, 255, 255, 255);
    tGraphics.DrawString("[2] Push state", m_Font, 10.0F, 150.0F, 255, 255, 255, 255);
}
