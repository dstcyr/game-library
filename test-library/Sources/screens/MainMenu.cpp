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
#include "screens/MainMenu.h"

void MainMenu::Enter()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    m_TitleImage.Initialize("textures/title_screen.png");
    m_TitleImage.Scale(1.5F);
    m_TitleImage.SetPadding(5.0F, 5.0F);

    m_CursorImage.Initialize("gui/cursor.png");
    m_CursorImage.Scale(1.5F);
    m_CursorImage.SetPadding(5.0F, 5.0F);

    m_SubTitleText.Initialize("fonts/junction.ttf", 18);
    m_SubTitleText.SetText("A mini-rpg adventure");
    m_SubTitleText.SetColor(255, 255, 255, 255);
    m_SubTitleText.SetPadding(280.0F, 5.0F);

    m_TitleBox.AddChild(&m_TitleImage);
    m_TitleBox.AddChild(&m_SubTitleText);
    m_TitleBox.SetPadding(10.0F, 10.0F);

    m_PlayText.Initialize("fonts/junction.ttf", 18, 150.0F, 40.0F);
    m_PlayText.SetText("New");
    m_PlayText.SetColor(255, 255, 255, 255);
    m_PlayText.SetPadding(5.0F, 5.0F);
    m_PlayText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
    m_OptionBox.AddChild(&m_PlayText);

    ISave& tSave = Game::Get().GetSave();
    m_SaveFileFound = tSave.Exists("jrpg.sav");
    if (m_SaveFileFound)
    {
        m_LoadText.Initialize("fonts/junction.ttf", 18, 150.0F, 40.0F);
        m_LoadText.SetText("Continue");
        m_LoadText.SetColor(255, 255, 255, 255);
        m_LoadText.SetPadding(5.0F, 5.0F);
        m_LoadText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
        m_OptionBox.AddChild(&m_LoadText);
    }

    m_ExitText.Initialize("fonts/junction.ttf", 18, 150.0F, 40.0F);
    m_ExitText.SetText("Exit");
    m_ExitText.SetColor(255, 255, 255, 255);
    m_ExitText.SetPadding(5.0F, 5.0F);
    m_ExitText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
    m_OptionBox.AddChild(&m_ExitText);

    m_OptionBox.SetPadding(10.0F, 10.0F);

    float titleW = m_TitleBox.GetWidth();
    m_TitlePosX = (static_cast<float>(screenW) / 2) - (titleW / 2);

    float optionW = m_OptionBox.GetWidth();
    m_OptionPosX = (static_cast<float>(screenW) / 2) - (optionW / 2);

    m_VersionText.Initialize("fonts/junction.ttf", 18, 80.0F, 40.0F);
    m_VersionText.SetText("0.0.6");
    m_VersionText.SetColor(255, 255, 255, 255);
    m_VersionText.SetPadding(5.0F, 5.0F);

    m_Options.emplace_back(885.0F, 561.0F);

    if (m_SaveFileFound)
    {
        m_Options.emplace_back(865.0F, 601.0F);
        m_Options.emplace_back(887.0F, 641.0F);
    }
    else
    {
        m_Options.emplace_back(887.0F, 601.0F);
    }

    m_SelectedOption = 0;
}

bool MainMenu::ProcessInput(float deltaTime)
{
    IInputs& tInput = Game::Get().Inputs();
    int len = static_cast<int>(m_Options.size());

    if (tInput.IsKeyPressed(EKey::EKEY_UP))
    {
        m_SelectedOption--;
        if (m_SelectedOption < 0)
        {
            m_SelectedOption = len - 1;
        }
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_DOWN))
    {
        m_SelectedOption++;
        if (m_SelectedOption > len - 1)
        {
            m_SelectedOption = 0;
        }
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_RETURN))
    {
        if (m_SelectedOption == 0)
        {
            IWorld& tWorld = Game::Get().World();
            tWorld.StartNewGame();
        }
        else if (m_SelectedOption == 1)
        {
            if (m_SaveFileFound)
            {
                ISave& tSave = Game::Get().GetSave();
                tSave.Load("jrpg.sav");
            }
            else
            {
                Game::Get().QuitGame();
            }
        }
        else
        {
            Game::Get().QuitGame();
        }
    }

    return true;
}

void MainMenu::Draw()
{
    m_TitleBox.Draw(m_TitlePosX, 150.0F);
    m_OptionBox.Draw(m_OptionPosX, 550.0F);
    m_CursorImage.Draw(m_Options[m_SelectedOption].first, m_Options[m_SelectedOption].second);

    IGraphics& tGraphics = Game::Get().Graphics();
    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);
    m_VersionText.Draw(screenW - 100.0F, screenH - 50.0F);
}

void MainMenu::Exit()
{
    m_TitleBox.Clear();
    m_OptionBox.Clear();
}
