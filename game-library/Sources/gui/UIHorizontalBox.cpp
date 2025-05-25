//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UIHorizontalBox.h"

float UIHorizontalBox::GetWidth() const
{
    float totalWidth = 0.0F;
    for (UINode* node : m_Children)
    {
        totalWidth += node->GetWidth();
    }

    return totalWidth + m_PaddingX + m_PaddingX;
}

float UIHorizontalBox::GetHeight() const
{
    float maxHeight = 0.0F;
    for (UINode* node : m_Children)
    {
        if (maxHeight < node->GetHeight())
        {
            maxHeight = node->GetHeight();
        }
    }

    return maxHeight + m_PaddingY + m_PaddingY;
}

void UIHorizontalBox::Draw(float posX, float posY)
{
    IGraphics& tGraphics = Game::Get().Graphics();

    float yy = posY + m_PaddingY;
    float xx = posX + m_PaddingX;
    for (UINode* node : m_Children)
    {
        node->Draw(xx, yy);
        xx += node->GetWidth();
    }

#if defined(DEBUG_UI)
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 0, 255, 255, 255);
#endif
}

void UIHorizontalBox::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}
