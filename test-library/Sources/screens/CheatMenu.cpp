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
#include "screens/CheatMenu.h"
#include "../../Includes/stats/IParty.h"
#include "../../Includes/combat/ICombat.h"
#include "../../Includes/stats/Party.h"
#include "../../Includes/combat/CombatManager.h"

void CheatMenu::Enter()
{
    if (!m_Initialized)
    {
        m_Initialized = true;

        IGraphics& tGraphics = Game::Get().Graphics();
        int screenW = 0;
        int screenH = 0;
        tGraphics.GetScreenSize(&screenW, &screenH);

        float border = 6.0F;
        std::string panelImage = "gui/simple_panel.png";

        int menuFontSize = 32;

        m_TitleText.Initialize("fonts/junction.ttf", menuFontSize, 600.0F, 60.0F);
        m_TitleText.SetText("Cheating Menu");
        m_TitleText.SetColor(255, 255, 255, 255);
        m_TitleText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
        m_TitleText.SetPadding(5.0F, 5.0F);

        m_TopTitlePanel.Initialize(panelImage, 600.0F, 70.0F, border);
        m_TopTitlePanel.SetChild(&m_TitleText);
        m_TopTitlePanel.SetPadding(5.0F, 5.0F);

        float titleW = m_TopTitlePanel.GetWidth();
        m_TitlePosX = (static_cast<float>(screenW) / 2) - (titleW / 2);

        m_OptionPanel.Initialize(panelImage, 600.0F, screenH - 150.0F, border);
        m_OptionPanel.SetPadding(5.0F, 5.0F);

        m_DamageText.Initialize("fonts/junction.ttf", menuFontSize);
        m_DamageText.SetText("Take 10 damage");
        m_DamageText.SetColor(255, 255, 255, 255);
        m_DamageText.SetPadding(5.0F, 5.0F);

        m_HealText.Initialize("fonts/junction.ttf", menuFontSize);
        m_HealText.SetText("Heal 10 damage");
        m_HealText.SetColor(255, 255, 255, 255);
        m_HealText.SetPadding(5.0F, 5.0F);

        m_XpText.Initialize("fonts/junction.ttf", menuFontSize);
        m_XpText.SetText("Gain 300 xp");
        m_XpText.SetColor(255, 255, 255, 255);
        m_XpText.SetPadding(5.0F, 5.0F);

        m_MegaXpText.Initialize("fonts/junction.ttf", menuFontSize);
        m_MegaXpText.SetText("Gain 4000 xp");
        m_MegaXpText.SetColor(255, 255, 255, 255);
        m_MegaXpText.SetPadding(5.0F, 5.0F);

        m_ThiefUnlock.Initialize("fonts/junction.ttf", menuFontSize);
        m_ThiefUnlock.SetText("Unlock Thief");
        m_ThiefUnlock.SetColor(255, 255, 255, 255);
        m_ThiefUnlock.SetPadding(5.0F, 5.0F);

        m_MageUnlock.Initialize("fonts/junction.ttf", menuFontSize);
        m_MageUnlock.SetText("Unlock Mage");
        m_MageUnlock.SetColor(255, 255, 255, 255);
        m_MageUnlock.SetPadding(5.0F, 5.0F);

        m_StartCombat.Initialize("fonts/junction.ttf", menuFontSize);
        m_StartCombat.SetText("Start Combat");
        m_StartCombat.SetColor(255, 255, 255, 255);
        m_StartCombat.SetPadding(5.0F, 5.0F);

        m_StartStory.Initialize("fonts/junction.ttf", menuFontSize);
        m_StartStory.SetText("Start Story");
        m_StartStory.SetColor(255, 255, 255, 255);
        m_StartStory.SetPadding(5.0F, 5.0F);

        m_Options.AddChild(&m_DamageText);
        m_Options.AddChild(&m_HealText);
        m_Options.AddChild(&m_XpText);
        m_Options.AddChild(&m_MegaXpText);
        m_Options.AddChild(&m_ThiefUnlock);
        m_Options.AddChild(&m_MageUnlock);
        m_Options.AddChild(&m_StartCombat);
        m_Options.AddChild(&m_StartStory);
        m_Options.SetPadding(50.0F, 10.0F);

        m_OptionPanel.SetChild(&m_Options);

        m_CursorImage.Initialize("gui/cursor.png");
        m_CursorImage.Scale(1.5F);
        m_CursorImage.SetPadding(5.0F, 5.0F);
      
        float start = 155.0F;
        for (int i = 0; i < m_Options.Count(); i++)
        {
            m_OptionList.push_back(start);
            start += 45.0F;
        }

        m_MainBox.AddChild(&m_TopTitlePanel);
        m_MainBox.AddChild(&m_OptionPanel);
    }

    m_SelectedOption = 0;
}

bool CheatMenu::ProcessInput(float deltaTime)
{
    IWorld& tWorld = Game::Get().World();
    IInputs& tInput = Game::Get().Inputs();
    int len = static_cast<int>(m_OptionList.size());

    if (tInput.IsKeyPressed(EKey::EKEY_ESCAPE))
    {
        tWorld.PopState();
    }

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
        IWorld& tWorld = Game::Get().World();
        IParty& tParty = Party::Get();

        if (m_SelectedOption == 0)
        {
            BX_LOG(ELogLevel::Log, "CHEAT: take damage");
            tParty.TakeDamage("Zest", 10.0F);

        }
        else if (m_SelectedOption == 1)
        {
            BX_LOG(ELogLevel::Log, "CHEAT: heal damage");
            tParty.Heal("Zest", 10.0F);

        }
        else if (m_SelectedOption == 2)
        {
            BX_LOG(ELogLevel::Log, "CHEAT: gain xp");
            tParty.GainXp(300);
        }
        else if (m_SelectedOption == 3)
        {
            BX_LOG(ELogLevel::Log, "CHEAT: gain xp");
            tParty.GainXp(4000);
        }
        else if (m_SelectedOption == 4)
        {
            BX_LOG(ELogLevel::Log, "CHEAT: unlock thief");
            tParty.UnlockCharacter("Thief");
        }
        else if (m_SelectedOption == 5)
        {
            BX_LOG(ELogLevel::Log, "CHEAT: unlock mage");
            tParty.UnlockCharacter("Mage");
        }
        else if (m_SelectedOption == 6)
        {
            ICombat& tCombat = CombatManager::Get();
            tCombat.StartCombat();
            return false;
        }
        else if (m_SelectedOption == 7)
        {
            tWorld.ReplaceState("Story");
            return false;
        }

        tWorld.PopState();
    }

    return false;
}

void CheatMenu::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.EnableCamera(false);
    m_MainBox.Draw(m_TitlePosX, 50.0F);
    m_CursorImage.Draw(650.0F, m_OptionList[m_SelectedOption]);
    tGraphics.EnableCamera(true);
}
