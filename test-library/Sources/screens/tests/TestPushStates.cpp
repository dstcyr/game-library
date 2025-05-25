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
#include "screens/tests/TestPushStates.h"

void TestPushStates::Enter()
{
    BX_LOG(ELogLevel::Log, "TestPushStates::Enter");
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);
}

void TestPushStates::Update(float deltaTime)
{
    IInputs& tInputs = Game::Get().Inputs();
    if (tInputs.IsKeyPressed(EKey::EKEY_1))
    {
        Game::Get().World().PopState();
    }
}

void TestPushStates::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawString("Test Game States", m_Font, 10.0F, 10.0F, 0, 255, 255, 255);
    tGraphics.DrawString("[1] Pop state", m_Font, 10.0F, 100.0F, 0, 255, 255, 255);
}
