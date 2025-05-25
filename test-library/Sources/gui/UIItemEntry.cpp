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
#include "gui/UIItemEntry.h"

UINode* UIItemEntry::Create(const std::string& text, int stack, const std::string& image, const std::string& frame)
{
    IGraphics& tGraphics = Game::Get().Graphics();

    auto* entry = new UIItemEntry();
    entry->m_ItemImage.Initialize(image);
    entry->m_ItemImage.SetPadding(10.0F, 25.0F);
    entry->m_ItemBox.AddChild(&entry->m_ItemImage);

    entry->m_ItemText.Initialize("fonts/junction.ttf", 24, 300.0F, 70.0F);
    entry->m_ItemText.SetAlign(EHAlignContent::LEFT, EVAlignContent::MIDDLE);
    entry->m_ItemText.SetText(text);
    entry->m_ItemText.SetColor(255, 255, 255, 255);
    //entry->m_ItemText.SetPadding(50.0F, 50.0F);
    entry->m_ItemBox.AddChild(&entry->m_ItemText);

    entry->m_StackText.Initialize("fonts/junction.ttf", 24, 80.0F, 70.0F);
    entry->m_StackText.SetAlign(EHAlignContent::RIGHT, EVAlignContent::MIDDLE);
    entry->m_StackText.SetText("x" + std::to_string(stack));
    entry->m_StackText.SetColor(255, 255, 255, 255);
    //entry->m_StackText.SetPadding(50.0F, 50.0F);
    entry->m_ItemBox.AddChild(&entry->m_StackText);

    return entry;
}

void UIItemEntry::Draw(float posX, float posY)
{
    m_ItemBox.Draw(posX, posY);
}

float UIItemEntry::GetWidth() const
{
    return m_ItemBox.GetWidth();
}

float UIItemEntry::GetHeight() const
{
    return m_ItemBox.GetHeight();
}
