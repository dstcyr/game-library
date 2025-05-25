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
#include "screens/tests/TestFade.h"

void TestFade::Enter()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);
}

void TestFade::Update(float deltaTime)
{
    IInputs& tInputs = Game::Get().Inputs();
    if (tInputs.IsKeyPressed(EKey::EKEY_1))
    {
        auto fadeInLambda = [this]() {
            BX_LOG(ELogLevel::Log, "Fade In Completed");
            };

        m_Fade.FadeIn(fadeInLambda);
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_2))
    {
        auto fadeOutLambda = [this]() {
            BX_LOG(ELogLevel::Log, "Fade Out Completed");
            };

        m_Fade.FadeOut(fadeOutLambda, true);
    }

    m_Fade.Update(deltaTime);
}

void TestFade::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    tGraphics.DrawRect(500, 500, 200, 150, 255, 0, 0, 255);
    tGraphics.DrawRect(800, 200, 200, 150, 255, 0, 0, 255);
    tGraphics.DrawRect(200, 800, 200, 150, 255, 0, 0, 255);
    tGraphics.DrawRect(1000, 800, 200, 150, 255, 0, 0, 255);

    m_Fade.Draw();

    tGraphics.DrawString("Test Fade", m_Font, 10.0F, 10.0F, 255, 255, 255, 255);
    tGraphics.DrawString("[1] Fade IN", m_Font, 10.0F, 100.0F, 255, 255, 255, 255);
    tGraphics.DrawString("[2] Fade OUT", m_Font, 10.0F, 150.0F, 255, 255, 255, 255);
}
