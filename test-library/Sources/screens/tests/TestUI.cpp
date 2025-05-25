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
#include "screens/tests/TestUI.h"
#include "gui/UIPanel.h"
#include "gui/UIText.h"

void TestUI::Enter()
{
    BX_LOG(ELogLevel::Log, "TestUI::Enter");
    IGraphics& tGraphics = Game::Get().Graphics();
    m_Font = tGraphics.LoadFont("fonts/pico8.ttf", 28);

    m_TextTest.Initialize("fonts/junction.ttf", 18, 500.0F, 100.0F);
    m_TextTest.SetText("This is a test");
    m_TextTest.SetColor(255, 255, 255, 255);
    m_TextTest.SetPadding(10.0F, 10.0F);
    m_TextTest.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);

    m_ImageTest.Initialize("textures/thief_portrait.png");
    m_ImageTest.SetPadding(10.0F, 10.0F);

    m_ProgressTest.Initialize(300.0F, 20.0F);
    m_ProgressTest.SetProgress(0.75F);
    m_ProgressTest.SetColor(255, 0, 0, 255);
    m_ProgressTest.SetPadding(10.0F, 10.0F);

    m_VerticalSeparatorTest.Initialize(80.0F, 50.0F);
    m_HorizontalSeparatorTest.Initialize(50.0F, 80.0F);

    m_VerticalTest.AddChild(&m_ImageTest);
    m_VerticalTest.AddChild(&m_VerticalSeparatorTest);
    m_VerticalTest.AddChild(&m_ImageTest);
    m_VerticalTest.AddChild(&m_TextTest);
    m_VerticalTest.SetPadding(10.0F, 10.0F);

    m_HorizontalTest.AddChild(&m_ImageTest);
    m_HorizontalTest.AddChild(&m_HorizontalSeparatorTest);
    m_HorizontalTest.AddChild(&m_ImageTest);
    m_HorizontalTest.SetPadding(10.0F, 10.0F);

    m_PanelTest.Initialize("gui/simple_panel.png", 300.0F, 200.0F, 3.0F);
    m_PanelTest.SetChild(&m_HorizontalTest);
    m_PanelTest.SetPadding(10.0F, 10.0F);
}

void TestUI::Update(float deltaTime)
{
}

void TestUI::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawString("Test UI", m_Font, 10.0F, 10.0F, 0, 0, 255, 255);

    m_TextTest.Draw(900.0F, 100.0F);
    m_ImageTest.Draw(300.0F, 100.0F);
    m_ProgressTest.Draw(500.0F, 100.0F);
    m_PanelTest.Draw(100.0F, 300.0F);
    m_VerticalTest.Draw(500.0F, 300.0F);
    m_HorizontalTest.Draw(100.0F, 600.0F);
}
