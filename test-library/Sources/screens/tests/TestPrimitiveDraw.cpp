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
#include "screens/tests/TestPrimitiveDraw.h"

void TestPrimitiveDraw::Enter()
{
    BX_LOG(ELogLevel::Log, "TestPrimitiveDraw::Enter");

    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);
    m_Bg = tGraphics.LoadTexture("textures/combat_bg_field.png");
    m_Hero = tGraphics.LoadTexture("textures/hero.png");
}

void TestPrimitiveDraw::Update(float deltaTime)
{
    IInputs& tInput = Game::Get().Inputs();

    int mX = 0;
    int mY = 0;
    tInput.GetMousePosition(&mX, &mY);
    m_MouseX = static_cast<float>(mX);
    m_MouseY = static_cast<float>(mY);
    m_MouseDown = tInput.IsButtonDown(1);

    m_Angle += 20.0F * deltaTime;
}

void TestPrimitiveDraw::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawImage(m_Bg, 255, 255, 255, 255);
    tGraphics.DrawString("Test Primitive Draw", m_Font, 10.0F, 10.0F, 0, 0, 0, 255);
    tGraphics.DrawString("Test Primitive Draw", m_Font, 12.0F, 12.0F, 0, 0, 0, 100);

    int sW = 0;
    int sH = 0;
    tGraphics.GetScreenSize(&sW, &sH);
    auto screenW = static_cast<float>(sW);
    auto screenH = static_cast<float>(sH);

    if (m_MouseDown)
    {
        tGraphics.DrawLine(screenW / 2, screenH / 2, m_MouseX, m_MouseY, 255, 255, 0, 255);
    }

    tGraphics.DrawCross(m_MouseX, m_MouseY, 50.0F, 255, 255, 0, 255);
    tGraphics.DrawRect(100.0F, 100.0F, screenW - 200.0F, screenH - 200.0F, 255, 0, 0, 255);
    tGraphics.FillRect(100.0F, 100.0F, screenW - 200.0F, screenH - 200.0F, 255, 0, 0, 100);
    tGraphics.DrawImage(m_Hero, { 0, 0, 60, 98 }, { 100, 100, 60, 98 }, m_Angle, false, false, 255, 255, 255, 255);
    tGraphics.DrawImage(m_Hero, { 0, 0, 60, 98 }, { 300, 100, 60, 98 }, 0.0F, true, false, 255, 255, 255, 255);
    tGraphics.DrawImage(m_Hero, { 0, 0, 60, 98 }, { 500, 100, 60, 98 }, 0.0F, false, true, 255, 255, 255, 255);
    tGraphics.DrawImage(m_Hero, { 0, 0, 60, 98 }, { 700, 100, 60, 98 }, 0.0F, true, true, 255, 255, 255, 255);
}
