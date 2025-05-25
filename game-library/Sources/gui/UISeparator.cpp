//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UISeparator.h"

void UISeparator::Initialize(float w, float h)
{
    m_Width = w;
    m_Height = h;
}

float UISeparator::GetWidth() const
{
    return m_Width;
}

float UISeparator::GetHeight() const
{
    return m_Height; 
}

void UISeparator::Draw(float posX, float posY)
{
#if defined(DEBUG_UI)
    IGraphics& tGraphics = Game::Get().Graphics();
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.FillRect(posX, posY, width, height, 255, 0, 0, 60);
    tGraphics.DrawRect(posX, posY, width, height, 255, 0, 0, 255);
    tGraphics.DrawLine(posX, posY, posX + width, posY + height, 255, 0, 0, 60);
    tGraphics.DrawLine(posX + width, posY, posX, posY + height, 255, 0, 0, 60);
#endif
}