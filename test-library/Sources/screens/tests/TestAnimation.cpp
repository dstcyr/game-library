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
#include "screens/tests/TestAnimation.h"

void TestAnimation::Enter()
{
    BX_LOG(ELogLevel::Log, "TestAnimation::Enter");

    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);

    m_TestAnimation.Load("textures/walk_cycle32.png");
    m_TestAnimation.Init(16, 32, 48);
    m_TestAnimation.AddClip("up", 32, 4, 0.15F);
    m_TestAnimation.AddClip("right", 36, 4, 0.15F);
    m_TestAnimation.AddClip("down", 40, 4, 0.15F);
    m_TestAnimation.AddClip("left", 44, 4, 0.15F);
    m_TestAnimation.SetFrame("down");
}

void TestAnimation::Update(float deltaTime)
{
    IInputs& tInputs = Game::Get().Inputs();
    if (tInputs.IsKeyPressed(EKey::EKEY_1))
    {
        m_TestAnimation.SetFrame("up");
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_2))
    {
        m_TestAnimation.SetFrame("right");
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_3))
    {
        m_TestAnimation.SetFrame("down");
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_4))
    {
        m_TestAnimation.SetFrame("left");
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_UP) || tInputs.IsKeyPressed(EKey::EKEY_W))
    {
        m_TestAnimation.Play("up", m_Looping);
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_RIGHT) || tInputs.IsKeyPressed(EKey::EKEY_D))
    {
        m_TestAnimation.Play("right", m_Looping);
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_DOWN) || tInputs.IsKeyPressed(EKey::EKEY_S))
    {
        m_TestAnimation.Play("down", m_Looping);
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_LEFT) || tInputs.IsKeyPressed(EKey::EKEY_A))
    {
        m_TestAnimation.Play("left", m_Looping);
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_5))
    {
        m_Looping = !m_Looping;
    }
    if (tInputs.IsKeyPressed(EKey::EKEY_SPACE))
    {
        m_TestAnimation.Stop();
    }

    m_TestAnimation.Update(deltaTime);
}

void TestAnimation::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    std::string looping = (m_Looping) ? std::string("true") : std::string("false");

    tGraphics.DrawString("Test Animation", m_Font, 10.0F, 10.0F, 0, 255, 255, 255);
    tGraphics.DrawString("[1] Set frame up", m_Font, 10.0F, 100.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[2] Set frame right", m_Font, 10.0F, 150.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[3] Set frame down", m_Font, 10.0F, 200.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[4] Set frame left", m_Font, 10.0F, 250.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[UP] Play up", m_Font, 10.0F, 300.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[RIGHT] Play right", m_Font, 10.0F, 350.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[DOWN] Play down", m_Font, 10.0F, 400.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[LEFT] Play Left", m_Font, 10.0F, 450.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[5] Looping : " + looping, m_Font, 10.0F, 500.0F, 255, 255, 0, 255);
    tGraphics.DrawString("[SPACE] Stop", m_Font, 10.0F, 550.0F, 255, 255, 0, 255);

    int sW = 0;
    int sH = 0;
    tGraphics.GetScreenSize(&sW, &sH);

    float imageW = 192.0F;
    float imageH = 288.0F;
    float centerX = static_cast<float>(sW / 2.0F) - (imageW / 2);
    float centerY = static_cast<float>(sH / 2.0F) - (imageH / 2);
    m_TestAnimation.Draw(centerX, centerY, imageW, imageH, 0.0F);
}

