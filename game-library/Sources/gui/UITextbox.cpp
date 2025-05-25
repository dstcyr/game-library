//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UITextbox.h"

UITextbox* UITextbox::Create(const std::string& text, float posX, float posY)
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    UITextbox* textbox = new UITextbox();
    textbox->m_PosX = posX;
    textbox->m_PosY = posY;
    textbox->m_Panel.Initialize("gui/simple_panel.png", 100.0F, 100.0F, 6.0F);
    textbox->m_Panel.SetFitContent(true);

    textbox->m_Text.Initialize("fonts/junction.ttf", 24);
    textbox->m_Text.SetText("Take Him!");
    textbox->m_Text.SetPadding(10.0F, 10.0F);
    textbox->m_Text.SetColor(255, 255, 255, 255);

    textbox->m_Panel.SetChild(&textbox->m_Text);
    return textbox;
}

bool UITextbox::ProcessInput(float deltaTime)
{
    return true;
}

void UITextbox::Draw(float posX, float posY)
{
    m_Panel.Draw(posX, posY);
}

void UITextbox::Draw()
{
    Draw(m_PosX, m_PosY);
}

float UITextbox::GetWidth() const
{
    return m_Panel.GetWidth();
}

float UITextbox::GetHeight() const
{
    return m_Panel.GetHeight();
}

void UITextbox::Clear()
{
}
