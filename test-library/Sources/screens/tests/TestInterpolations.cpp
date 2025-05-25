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
#include "screens/tests/TestInterpolations.h"
#include "maths/Tween.h"

void TestInterpolations::Enter()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);

    int sW = 0;
    int sH = 0;
    tGraphics.GetScreenSize(&sW, &sH);
    m_ScreenW = static_cast<float>(sW);
    m_ScreenH = static_cast<float>(sH);

    m_Dest = (m_ScreenW - 50.0F) - 100.0F;
}

void TestInterpolations::Update(float deltaTime)
{
    IInputs& tInput = Game::Get().Inputs();
    if (tInput.IsKeyPressed(EKey::EKEY_SPACE))
    {
        m_Elapsed = 0.0F;
    }

    m_Elapsed += deltaTime;
    if (m_Elapsed >= m_Duration)
    {
        m_Elapsed = m_Duration;
    }

    m_LinearX = Tween::Linear(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_CircularInX = Tween::CircularIn(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_CircularOutX = Tween::CircularOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_CircularInOutX = Tween::CircularInOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_SinusoidalInX = Tween::SinusoidalIn(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_SinusoidalInOutX = Tween::SinusoidalInOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_SinusoidalOutX = Tween::SinusoidalOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_BackInX = Tween::BackIn(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_BackOutX = Tween::BackOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_BackInOutX = Tween::BackInOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_BounceInX = Tween::BounceIn(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_BounceOutX = Tween::BounceOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_BounceInOutX = Tween::BounceInOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_ElasticInX = Tween::ElasticIn(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_ElasticOutX = Tween::ElasticOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
    m_ElasticInOutX = Tween::ElasticInOut(m_Elapsed, 0.0F, m_Dest, m_Duration);
}

void TestInterpolations::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawString("Test Interpolations", m_Font, 10.0F, 10.0F, 0, 255, 255, 255);
    tGraphics.DrawString("[SPACE] Reset", m_Font, 10.0F, 80.0F, 0, 255, 255, 255);
    tGraphics.DrawString("Elapsed: " + std::to_string(m_Elapsed), m_Font, 10.0F, 150.0F, 255, 255, 0, 255);

    tGraphics.DrawLine(m_Dest + 25, 0, m_Dest + 25, m_ScreenH, 255, 0, 0, 100);

    float tY = 240.0F;
    tGraphics.DrawString("Linear", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_LinearX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("CircularIn", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_CircularInX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("CircularOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_CircularOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("CircularInOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_CircularInOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("SinusoidalIn", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_SinusoidalInX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("SinusoidalOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_SinusoidalOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("SinusoidalInOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_SinusoidalInOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("BackIn", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_BackInX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("BackOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_BackOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("BackInOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_BackInOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("BounceIn", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_BounceInX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("BounceOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_BounceOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("BounceInOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_BounceInOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("ElasticIn", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_ElasticInX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("ElasticOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_ElasticOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);

    tY += 27.0F;
    tGraphics.DrawString("ElasticInOut", m_Font, 10.0F, tY, 0, 255, 255, 255);
    tGraphics.FillRect(m_ElasticInOutX, tY, 50.0F, 50.0F, 255, 0, 0, 255);
    tY += 25.0F;
    tGraphics.DrawLine(0.0F, tY, m_ScreenW, tY, 255, 0, 0, 100);
}
