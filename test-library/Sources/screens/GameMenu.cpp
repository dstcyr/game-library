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
#include "screens/GameMenu.h"
#include "gui/UIItemEntry.h"
#include "../../Includes/stats/Party.h"

void GameMenu::Enter()
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

        m_TitleText.Initialize("fonts/junction.ttf", menuFontSize, 1287.0F, 60.0F);
        m_TitleText.SetText("Game Menu");
        m_TitleText.SetColor(255, 255, 255, 255);
        m_TitleText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
        m_TitleText.SetPadding(5.0F, 5.0F);

        m_HintText.Initialize("fonts/junction.ttf", menuFontSize, 970.0F, 60.0F);
        m_HintText.SetText("");
        m_HintText.SetColor(255, 255, 255, 255);
        m_HintText.SetAlign(EHAlignContent::LEFT, EVAlignContent::MIDDLE);
        m_HintText.SetPadding(10.0F, 5.0F);

        m_TopTitlePanel.Initialize(panelImage, 1300.0F, 70.0F, border);
        m_TopTitlePanel.SetChild(&m_TitleText);
        m_TopTitlePanel.SetPadding(5.0F, 5.0F);

        float titleW = m_TopTitlePanel.GetWidth();
        m_TitlePosX = (static_cast<float>(screenW) / 2) - (titleW / 2);

        m_OptionPanel.Initialize(panelImage, 300.0F, 600.0F, border);
        m_OptionPanel.SetPadding(5.0F, 5.0F);

        m_InfoPanel.Initialize(panelImage, 300.0F, 200.0F, border);
        m_InfoPanel.SetPadding(5.0F, 5.0F);

        m_OptionBox.AddChild(&m_OptionPanel);
        m_OptionBox.AddChild(&m_InfoPanel);

        m_PartyPanel.Initialize(panelImage, 990.0F, 725.0F, border);
        m_PartyPanel.SetPadding(5.0F, 5.0F);

        m_HintPanel.Initialize(panelImage, 990.0F, 74.0F, border);
        m_HintPanel.SetPadding(5.0F, 5.0F);
        m_HintPanel.SetChild(&m_HintText);

        m_MenuBox.AddChild(&m_TopTitlePanel);
        m_MenuBox.AddChild(&m_BottomBox);

        m_ItemsText.Initialize("fonts/junction.ttf", menuFontSize);
        m_ItemsText.SetText("Items");
        m_ItemsText.SetColor(255, 255, 255, 255);
        m_ItemsText.SetPadding(20.0F, 20.0F);

        m_StatusText.Initialize("fonts/junction.ttf", menuFontSize);
        m_StatusText.SetText("Status");
        m_StatusText.SetColor(255, 255, 255, 255);
        m_StatusText.SetPadding(20.0F, 20.0F);

        m_SaveText.Initialize("fonts/junction.ttf", menuFontSize);
        m_SaveText.SetText("Save");
        m_SaveText.SetColor(255, 255, 255, 255);
        m_SaveText.SetPadding(20.0F, 20.0F);

        m_LoadText.Initialize("fonts/junction.ttf", menuFontSize);
        m_LoadText.SetText("Load");
        m_LoadText.SetColor(255, 255, 255, 255);
        m_LoadText.SetPadding(20.0F, 20.0F);

        m_QuitText.Initialize("fonts/junction.ttf", menuFontSize);
        m_QuitText.SetText("Quit");
        m_QuitText.SetColor(255, 255, 255, 255);
        m_QuitText.SetPadding(20.0F, 20.0F);

        m_Options.AddChild(&m_ItemsText);
        m_Options.AddChild(&m_StatusText);
        m_Options.AddChild(&m_SaveText);
        m_Options.AddChild(&m_LoadText);
        m_Options.AddChild(&m_QuitText);
        m_Options.SetPadding(40.0F, 20.0F);

        m_OptionPanel.SetChild(&m_Options);

        m_CursorImage.Initialize("gui/cursor.png");
        m_CursorImage.Scale(1.5F);
        m_CursorImage.SetPadding(5.0F, 5.0F);

        m_OptionList.push_back(177.0F);
        m_OptionList.push_back(250.0F);
        m_OptionList.push_back(323.0F);
        m_OptionList.push_back(396.0F);
        m_OptionList.push_back(469.0F);



        // m_PartyBox.AddChild(&m_PartyEntry);
        // m_PartyBox.AddChild(&m_PartyEntry);
        m_PartyBox.SetPadding(10.0F, 10.0F);

        m_PartyPanel.SetChild(&m_PartyBox);

        m_MainBox.AddChild(&m_PartyPanel);
        m_MainBox.AddChild(&m_HintPanel);

        m_BottomBox.AddChild(&m_OptionBox);
        m_BottomBox.AddChild(&m_MainBox);
    }

    IParty& tParty = Party::Get();
    BX_CHECKS(m_PartyBox.Count() == 0, "UI already initialized");

    std::vector<FCharacterDefinition*> party = tParty.GetPartyDefinition();

    for (FCharacterDefinition* character : party)
    {
        auto* entry = new UIPartyEntry();
        m_PartyEntries.emplace_back(entry);

        entry->Initialize();
        entry->SetPadding(20.0F, 20.0F);
        entry->SetInfo(character);
        m_PartyBox.AddChild(entry);
    }

    m_SelectedOption = 0;
    UpdateHintText();
}

bool GameMenu::ProcessInput(float deltaTime)
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

        UpdateHintText();
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_DOWN))
    {
        m_SelectedOption++;
        if (m_SelectedOption > len - 1)
        {
            m_SelectedOption = 0;
        }

        UpdateHintText();
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_RETURN))
    {
        ISave& tSave = Game::Get().GetSave();

        if (m_SelectedOption == 0)
        {
            m_PartyPanel.Clear();

            auto* vbox1 = new UIVerticalBox();

            // TODO (DaSt):
            /// auto slots = Game::Get().Inventory().GetItems();
            /// for (auto it = slots.begin(); it != slots.end(); it++)
            /// {
            ///     FItems id = (*it).itemID;
            ///     const FItemDefinition& item = FItemDatabase::GetItemDefinition(id);
            ///     int count = (*it).count;
            ///     std::string itemName = item.name;
            /// 
            ///     vbox1->AddChild(UIItemEntry::Create(itemName, count, "textures/potion.png", "potion"));
            /// }


            // vbox1->AddChild(UIItemEntry::Create("Small potion", 1, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 20, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 300, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox1->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            vbox1->SetPadding(20.0F, 20.0F);

            auto* vbox2 = new UIVerticalBox();
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            // vbox2->AddChild(UIItemEntry::Create("Small potion", 4000, "textures/potion.png", "test"));
            vbox2->SetPadding(20.0F, 20.0F);

            auto* hBox = new UIHorizontalBox();
            auto* seperator = new UISeparator();
            seperator->Initialize(50.0F, 100.0F);

            hBox->AddChild(vbox1);
            hBox->AddChild(seperator);
            hBox->AddChild(vbox2);

            m_PartyPanel.SetChild(hBox);
        }
        else if (m_SelectedOption == 2)
        {
            tSave.Save("jrpg.sav");
            tWorld.PopState();
        }
        else if (m_SelectedOption == 3)
        {
            tSave.Load("jrpg.sav");
        }
        else if (m_SelectedOption == 4)
        {
            Game::Get().QuitGame();
        }
    }

    return false;
}

void GameMenu::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.EnableCamera(false);
    m_MenuBox.Draw(m_TitlePosX, 50.0F);
    m_CursorImage.Draw(310.0F, m_OptionList[m_SelectedOption]);
    tGraphics.EnableCamera(true);
}

void GameMenu::Exit()
{
    for (auto it = m_PartyBox.Begin(); it != m_PartyBox.End(); it++)
    {
        delete* it;
    }

    m_PartyBox.Clear();
}

void GameMenu::Destroy()
{
    Exit();
}

void GameMenu::UpdateHintText()
{
    if (m_SelectedOption == 0)
    {
        m_HintText.SetText("Open the inventory");
    }
    else if (m_SelectedOption == 1)
    {
        m_HintText.SetText("Open the status");
    }
    else if (m_SelectedOption == 2)
    {
        m_HintText.SetText("Save the game");
    }
    else if (m_SelectedOption == 3)
    {
        m_HintText.SetText("Load the game");
    }
    else if (m_SelectedOption == 4)
    {
        m_HintText.SetText("Quit the game");
    }
}
