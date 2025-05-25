//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

void Fade::Init(bool startOut)
{
    m_FadingOut = startOut;
    m_FadeAlpha = startOut ? 255 : 0;
}

void Fade::Update(float deltaTime)
{
    if (m_Fading)
    {
        m_Elapsed += deltaTime;
        if (m_Elapsed >= m_FadeSpeed)
        {
            m_Elapsed = 0.0F;
            if (m_FadingOut)
            {
                m_FadeAlpha += m_FadeInc;
                if (m_FadeAlpha >= 255)
                {
                    m_FadeAlpha = 255;
                    m_Fading = false;
                    if (FadeOutCallback)
                    {
                        FadeOutCallback();
                    }
                }
            }
            else
            {
                m_FadeAlpha -= m_FadeInc;
                if (m_FadeAlpha <= 0)
                {
                    m_FadeAlpha = 0;
                    m_Fading = false;
                    if (FadeInCallback)
                    {
                        FadeInCallback();
                    }
                }
            }
        }
    }
}

void Fade::Draw()
{
    if (m_Fading || (m_FadingOut && m_Hold))
    {
        IGraphics& tGraphics = Game::Get().Graphics();
        UpdateScreenSize();
    
        tGraphics.EnableCamera(false);
        tGraphics.FillRect(0.0F, 0.0F, m_ScreenWidth, m_ScreenHeight, 0, 0, 0, m_FadeAlpha);
        tGraphics.EnableCamera(true);
    }
}

void Fade::FadeIn(const std::function<void()>& callback)
{
    if (!m_Fading && m_FadingOut)
    {
        m_Fading = true;
        m_FadingOut = false;
        m_FadeAlpha = 255;
        m_Elapsed = 0.0F;

        FadeInCallback = callback;
    }
}

void Fade::FadeIn()
{
    FadeIn([]() {});
}

void Fade::FadeOut(const std::function<void()>& callback, bool bHold)
{
    if (!m_Fading && !m_FadingOut)
    {
        m_Fading = true;
        m_FadingOut = true;
        m_FadeAlpha = 0;
        m_Elapsed = 0.0F;
        m_Hold = bHold;

        FadeOutCallback = callback;
    }
}

void Fade::FadeOut(bool bHold)
{
    FadeOut([]() {}, bHold);
}

void Fade::SetSpeed(float speed, int inc)
{
    m_FadeSpeed = speed;
    m_FadeInc = inc;
}

void Fade::UpdateScreenSize()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int sW = 0;
    int sH = 0;
    tGraphics.GetScreenSize(&sW, &sH);
    m_ScreenWidth = static_cast<float>(sW);
    m_ScreenHeight = static_cast<float>(sH);
}

std::function<void()> Fade::FadeInCallback;
std::function<void()> Fade::FadeOutCallback;
