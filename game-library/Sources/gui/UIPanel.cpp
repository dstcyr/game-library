//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "gui/UIPanel.h"

void UIPanel::Initialize(const std::string& filename, float width, float height, float border)
{
    m_Width = width;
    m_Height = height;
    m_Border = border;

    m_Image.Load(filename);
    m_Image.AddFrame("top-left", 0, 0, 3, 3);
    m_Image.AddFrame("top", 3, 0, 3, 3);
    m_Image.AddFrame("top-right", 6, 0, 3, 3);
    m_Image.AddFrame("middle-left", 0, 3, 3, 3);
    m_Image.AddFrame("middle", 3, 3, 3, 3);
    m_Image.AddFrame("middle-right", 6, 3, 3, 3);
    m_Image.AddFrame("bottom-left", 0, 6, 3, 3);
    m_Image.AddFrame("bottom", 3, 6, 3, 3);
    m_Image.AddFrame("bottom-right", 6, 6, 3, 3);
}

void UIPanel::Draw(float posX, float posY)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    float currentWidth = m_Width;
    float currentHeight = m_Height;

    if (m_Child != nullptr && m_FitContent)
    {
        currentWidth = m_Child->GetWidth() + m_Border + m_Border;
        currentHeight = m_Child->GetHeight() + m_Border + m_Border;
    }

    m_Image.Draw("top-left", posX + m_PaddingX, posY + m_PaddingY, m_Border, m_Border);
    m_Image.Draw("top", posX + m_PaddingX + m_Border, posY + m_PaddingY, currentWidth - m_Border - m_Border, m_Border);
    m_Image.Draw("top-right", posX + m_PaddingX + m_Border + currentWidth - m_Border - m_Border, posY + m_PaddingY, m_Border, m_Border);
    m_Image.Draw("middle-left", posX + m_PaddingX, posY + m_PaddingY + m_Border, m_Border, currentHeight - m_Border - m_Border);
    m_Image.Draw("middle", posX + m_PaddingX + m_Border, posY + m_PaddingY + m_Border, currentWidth - m_Border - m_Border, currentHeight - m_Border - m_Border);
    m_Image.Draw("middle-right", posX + m_PaddingX + m_Border + currentWidth - m_Border - m_Border, posY + m_PaddingY + m_Border, m_Border, currentHeight - m_Border - m_Border);
    m_Image.Draw("bottom-left", posX + m_PaddingX, posY + m_PaddingY + currentHeight - m_Border, m_Border, m_Border);
    m_Image.Draw("bottom", posX + m_PaddingX + m_Border, posY + m_PaddingY + currentHeight - m_Border, currentWidth - m_Border - m_Border, m_Border);
    m_Image.Draw("bottom-right", posX + m_PaddingX + m_Border + currentWidth - m_Border - m_Border, posY + m_PaddingY + currentHeight - m_Border, m_Border, m_Border);

#if defined(DEBUG_UI)
    float width = GetWidth();
    float height = GetHeight();
    tGraphics.DrawRect(posX, posY, width, height, 255, 255, 0, 255);
#endif

    if (m_Child != nullptr)
    {
        m_Child->Draw(posX + m_PaddingX + m_Border, posY + m_PaddingY + m_Border);
    }
}

float UIPanel::GetWidth() const
{
    if (m_Child != nullptr && m_FitContent)
    {
        return m_Child->GetWidth() + m_Border + m_Border + m_PaddingX + m_PaddingX;
    }

    return m_Width + m_PaddingX + m_PaddingX;
}

float UIPanel::GetHeight() const
{
    if (m_Child != nullptr && m_FitContent)
    {
        return m_Child->GetHeight() + m_Border + m_Border + m_PaddingY + m_PaddingY;
    }

    return m_Height + m_PaddingY + m_PaddingY;
}

void UIPanel::SetChild(UINode* node)
{
    m_Child = node;
}

void UIPanel::SetFitContent(bool fit)
{
    m_FitContent = fit;
}

void UIPanel::SetPadding(float x, float y)
{
    m_PaddingX = x;
    m_PaddingY = y;
}

void UIPanel::Clear()
{
    m_Child = nullptr;
}
