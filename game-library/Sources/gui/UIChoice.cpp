//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UIChoice.h"

void UIChoice::Create(const std::string& text, const std::vector<std::string>& dataSource, float posX, float posY, const std::function<void(int)>& callback)
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    auto* choice = new UIChoice();
    choice->m_ChoiceCallback = callback;
    choice->m_Panel.Initialize("gui/simple_panel.png", screenW - 600.0F, 90.0F, 6.0F);
    choice->m_Panel.SetFitContent(true);

    float textHeight = 0.0F;
    if (!text.empty())
    {
        choice->m_Text.Initialize("fonts/junction.ttf", 24);
        choice->m_Text.SetText(text);
        choice->m_Text.SetColor(255, 255, 255, 255);
        choice->m_OptionBox.AddChild(&choice->m_Text);

        textHeight = choice->m_Text.GetHeight();
    }

    choice->m_Separator.Initialize(10.0F, 10.0F);
    choice->m_OptionBox.AddChild(&choice->m_Separator);

    choice->m_CursorImage.Initialize("gui/cursor.png");
    choice->m_CursorImage.Scale(1.2F);
    float cursorHeight = choice->m_CursorImage.GetHeight();

    float optionX = 0.0F;
    float optionY = textHeight + choice->m_Separator.GetHeight();

    for (const auto& data : dataSource)
    {
        auto* nameText = new UIText();
        nameText->Initialize("fonts/junction.ttf", 24);
        nameText->SetText(data);
        nameText->SetColor(255, 255, 255, 255);
        nameText->SetPadding(35.0F, 5.0F);
        nameText->SetAlign(EHAlignContent::LEFT, EVAlignContent::MIDDLE);
        choice->m_OptionBox.AddChild(nameText);
        choice->m_Pointers.PushBack(nameText);

        float height = nameText->GetHeight();
        choice->AddOptionLocation(optionX, optionY + (height / 2.0F) - (cursorHeight / 4.0F) + 4.0F);
        optionY += height;
    }

    choice->m_PosX = posX;
    choice->m_PosY = posY;
    choice->m_OptionBox.SetPadding(5.0F, 5.0F);
    choice->m_Panel.SetChild(&choice->m_OptionBox);

    Game& tGame = Game::Get();
    tGame.PushUINode(choice);
}

bool UIChoice::ProcessInput(float deltaTime)
{
    IInputs& tInput = Game::Get().Inputs();
    int len = static_cast<int>(m_OptionLocations.size());

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
        Game& tGame = Game::Get();
        tGame.PopUINode();

        if (m_ChoiceCallback)
        {
            m_ChoiceCallback(m_SelectedOption);
        }
    }

    return false;
}

void UIChoice::Draw(float posX, float posY)
{
    m_Panel.Draw(posX, posY);

    Vec2<float> location = m_OptionLocations[m_SelectedOption];
    m_CursorImage.Draw(posX + location.x, posY + location.y);
}

void UIChoice::Draw()
{
    Draw(m_PosX, m_PosY);
}

float UIChoice::GetWidth() const
{
    return m_Panel.GetWidth();
}

float UIChoice::GetHeight() const
{
    return m_Panel.GetHeight();
}

void UIChoice::Clear()
{
    while (!m_Pointers.IsEmpty())
    {
        UINode* node = m_Pointers.PopBack();
        delete node;
    }

    m_OptionBox.Clear();
}

void UIChoice::AddOptionLocation(float posX, float posY)
{
    m_OptionLocations.emplace_back(posX, posY);
}
