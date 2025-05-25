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
#include "effects/FloatingNumber.h"
#include "scenes/Character.h"

IEffect* FloatingNumber::Create(Character* target, int num)
{
    auto* effect = new FloatingNumber();
    IGraphics& tGraphics = Game::Get().Graphics();
    effect->m_Target = target;
    effect->m_Font = tGraphics.LoadFont("fonts/junction.ttf", 24);

    effect->m_Target->GetWorldLocation(&effect->m_X, &effect->m_Y);

    float width = 0.0F;
    float height = 0.0F;
    effect->m_Target->GetSize(&width, &height);

    effect->m_X += (width / 2.0F);
    effect->m_Y += (height / 2.0F);

    effect->m_Gravity = 700.0F;
    effect->m_VelocityY = 224.0F;
    effect->m_FadeDistance = 33.0F;
    effect->m_Scale = 1.3F;
    effect->m_Number = num;

    int fontW = 0;
    int fontH = 0;
    tGraphics.GetTextSize(std::to_string(num), effect->m_Font, &fontW, &fontH);

    effect->m_X -= (fontW / 2.0F);
    effect->m_Y -= (fontH / 2.0F);
    effect->m_CurrentY = effect->m_Y;

    effect->m_Alpha = 255;
    effect->m_Priority = 1;

    return effect;
}

void FloatingNumber::Update(float deltaTime)
{
    m_CurrentY = m_CurrentY - (m_VelocityY * deltaTime);
    m_VelocityY = m_VelocityY - (m_Gravity * deltaTime);

    if (m_CurrentY >= m_Y)
    {
        float fade01 = std::abs((m_CurrentY - m_Y)) / m_FadeDistance;
        fade01 = (fade01 > 1.0F) ? 1.0F : fade01;
        auto invAlpha = static_cast<unsigned char>(255 * fade01);
        m_Alpha = 255 - invAlpha;
    }
}

void FloatingNumber::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawString(std::to_string(m_Number), m_Font, m_X, m_CurrentY, 255, 255, 255, m_Alpha);

#if defined(DEBUG_EFFECTS)
    tGraphics.DrawLine(m_X - 100.0F, m_Y, m_X + 100.0F, m_Y, 255, 0, 0, 255);
#endif
}

bool FloatingNumber::IsFinished()
{
    return m_CurrentY >= (m_Y + m_FadeDistance);
}
