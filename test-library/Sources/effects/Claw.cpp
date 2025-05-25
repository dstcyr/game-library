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
#include "effects/Claw.h"
#include "scenes/Character.h"

IEffect* Claw::Create(Character* target)
{
    IAudio& tAudio = Game::Get().Audio();
    size_t sfx = tAudio.LoadAudio("sounds/claw.wav");
    tAudio.PlaySFX(sfx);

    auto* effect = new Claw();
    IGraphics& tGraphics = Game::Get().Graphics();
    effect->m_Target = target;
    effect->m_Animation.Load("textures/combat_claw.png");
    effect->m_Animation.Init(3, 64, 64);
    effect->m_Animation.AddClip("claw", 0, 3, 0.05F);

    effect->m_Target->GetWorldLocation(&effect->m_X, &effect->m_Y);

    float width = 0.0F;
    float height = 0.0F;
    effect->m_Target->GetSize(&width, &height);

    effect->m_X += (width / 2.0F);
    effect->m_Y += (height / 2.0F);
    effect->m_X -= (64.0F / 2.0F);
    effect->m_Y -= (64.0F / 2.0F);

    effect->m_Priority = 2;
    effect->m_IsFinished = false;
    effect->m_Animation.PlayOnce("claw", [effect]() { effect->m_IsFinished = true; });

    return effect;
}

void Claw::Update(float deltaTime)
{
    m_Animation.Update(deltaTime);
}

void Claw::Draw()
{
    m_Animation.Draw(m_X, m_Y, 0.0F);
}

bool Claw::IsFinished()
{
    return m_IsFinished;
}
