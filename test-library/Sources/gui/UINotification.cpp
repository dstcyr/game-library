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
#include "gui/UINotification.h"

void UINotification::Create(const std::string& text, float delay)
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    auto* notification = new UINotification();
    notification->m_NoticePanel.Initialize("gui/simple_panel.png", screenW - 600.0F, 90.0F, 6.0F);
    notification->m_NoticeText.Initialize("fonts/junction.ttf", 24, screenW - 600.0F, 90.0F);
    notification->m_NoticeText.SetText(text);
    notification->m_NoticeText.SetColor(255, 255, 255, 255);
    notification->m_NoticeText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
    notification->m_NoticePanel.SetChild(&notification->m_NoticeText);

    float noticeWidth = notification->m_NoticePanel.GetWidth();
    float posX = (static_cast<float>(screenW) / 2.0F) - (noticeWidth / 2.0F);
    float posY = 50.0F;

    notification->m_PosX = posX;
    notification->m_PosY = posY;
    notification->m_Delay = delay;
    notification->m_Elapsed = 0.0F;
    
    Game& tGame = Game::Get();
    tGame.FlushUIStack();
    tGame.PushUINode(notification);
}

void UINotification::Update(float deltaTime)
{
    m_Elapsed += deltaTime;
    if (m_Elapsed >= m_Delay)
    {
        Game::Get().PopUINode();
    }
}

void UINotification::Draw(float posX, float posY)
{
    m_NoticePanel.Draw(posX, posY);
}

void UINotification::Draw()
{
    Draw(m_PosX, m_PosY);
}

float UINotification::GetWidth() const
{
    return 0.0F;
}

float UINotification::GetHeight() const
{
    return 0.0F;
}
