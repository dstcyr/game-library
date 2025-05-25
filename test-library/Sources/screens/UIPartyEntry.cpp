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
#include "screens/UIPartyEntry.h"
#include "stats/Party.h"

void UIPartyEntry::Initialize()
{
    int menuFontSize = 28;
    m_Name.Initialize("fonts/junction.ttf", menuFontSize);
    m_Name.SetColor(255, 255, 255, 255);
    m_Name.SetPadding(5.0F, 5.0F);

    m_Level.Initialize("fonts/junction.ttf", menuFontSize);
    m_Level.SetColor(255, 255, 255, 255);
    m_Level.SetPadding(5.0F, 5.0F);

    m_HPProgress.Initialize(300.0F, 15.0F);
    m_HPProgress.SetColor(255, 0, 0, 255);
    m_HPProgress.SetPadding(5.0F, 0.0F);

    m_MPProgress.Initialize(300.0F, 15.0F);
    m_MPProgress.SetColor(0, 0, 255, 255);
    m_MPProgress.SetPadding(5.0F, 0.0F);

    m_Hp.Initialize("fonts/junction.ttf", menuFontSize);
    m_Hp.SetText("HP ???/???");
    m_Hp.SetColor(255, 255, 255, 255);
    m_Hp.SetPadding(5.0F, 0.0F);

    m_HpBox.AddChild(&m_Hp);
    m_HpBox.AddChild(&m_HPProgress);
    m_HpBox.SetPadding(0.0F, 5.0F);

    m_Mp.Initialize("fonts/junction.ttf", menuFontSize);
    m_Mp.SetText("MP ???/???");
    m_Mp.SetColor(255, 255, 255, 255);
    m_Mp.SetPadding(5.0F, 0.0F);

    m_MpBox.AddChild(&m_Mp);
    m_MpBox.AddChild(&m_MPProgress);
    m_MpBox.SetPadding(0.0F, 5.0F);

    m_InfoSeparator.Initialize(500.0F, 3.0F);

    m_TextBox.AddChild(&m_Name);
    m_TextBox.AddChild(&m_Level);
    m_TextBox.AddChild(&m_HpBox);
    m_TextBox.AddChild(&m_MpBox);
    m_TextBox.AddChild(&m_InfoSeparator);
    m_TextBox.SetPadding(10.0F, 0.0F);

    m_NextLevel.Initialize("fonts/junction.ttf", menuFontSize);
    m_NextLevel.SetText("Next Level");
    m_NextLevel.SetColor(255, 255, 255, 255);

    m_NextLevelProgress.Initialize(200.0F, 20.0F);
    m_NextLevelProgress.SetColor(255, 100, 0, 255);

    m_NextLevelSeparator.Initialize(100.0F, 40.0F);

    m_NextLevelBox.AddChild(&m_NextLevelSeparator);
    m_NextLevelBox.AddChild(&m_NextLevel);
    m_NextLevelBox.AddChild(&m_NextLevelProgress);

    m_EntryBox.AddChild(&m_Portrait);
    m_EntryBox.AddChild(&m_TextBox);
    m_EntryBox.AddChild(&m_NextLevelBox);
}

void UIPartyEntry::Draw(float posX, float posY)
{
    m_EntryBox.Draw(posX + m_PaddingX, posY + m_PaddingY);

#if defined(DEBUG_UI)
    IGraphics& tGraphics = Game::Get().Graphics();
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 255, 0, 0, 255);
#endif
}

float UIPartyEntry::GetWidth() const
{
    return m_EntryBox.GetWidth() + m_PaddingX + m_PaddingX;
}

float UIPartyEntry::GetHeight() const
{
    return m_EntryBox.GetHeight() + m_PaddingY + m_PaddingY;
}

void UIPartyEntry::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}

void UIPartyEntry::SetInfo(const FCharacterDefinition* definition)
{
    AttributeSet as = definition->attributes;
    m_Name.SetText(definition->name);

    int level = as.GetLevel();
    m_Level.SetText("LV " + std::to_string(level));

    int xp = as.GetXp();
    int next = as.NextLevel();
    float xpPercent = xp / static_cast<float>(next);
    m_NextLevelProgress.SetProgress(xpPercent);

    m_Portrait.Initialize(definition->portrait);
    m_Portrait.Scale(2.5F);

    FloatModifier maxHealthAttribute = as.GetMaxHealthAttribute();
    int hpMaxValue = static_cast<int>(maxHealthAttribute.GetValue());
    int hpValue = static_cast<int>(as.GetHealth());
    std::string hpStr = "HP " + std::to_string(hpValue) + "/" + std::to_string(hpMaxValue);
    m_Hp.SetText(hpStr);

    float percent = hpValue / static_cast<float>(hpMaxValue);
    m_HPProgress.SetProgress(percent);

    FloatModifier maxMagicAttribute = as.GetMaxMagicAttribute();
    int mpMaxValue = static_cast<int>(maxMagicAttribute.GetValue());
    int mpValue = static_cast<int>(as.GetMagic());
    std::string mpStr = "MP " + std::to_string(mpValue) + "/" + std::to_string(mpMaxValue);
    m_Mp.SetText(mpStr);

    percent = mpValue / static_cast<float>(mpMaxValue);
    m_MPProgress.SetProgress(percent);
}
