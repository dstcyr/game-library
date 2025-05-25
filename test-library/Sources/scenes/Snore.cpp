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
#include "scenes/Snore.h"

Entity* Snore::Create(const std::string& name)
{
    size_t uid = Utils::GenerateID(name);
    Snore* newInst = new Snore(uid, name);
    newInst->Initialize();
    return newInst;
}

Snore::Snore(size_t instId, const std::string& name) :
    Entity(instId, name)
{
}

void Snore::Initialize()
{
    m_SleepAnimation.Load("textures/sleeping.png");
    m_SleepAnimation.Init(4, 32, 32);
    m_SleepAnimation.AddClip("snore", 0, 4, 0.5F);
    m_SleepAnimation.Play("snore", true);
    SetSize(32.0F, 32.0F);
}

void Snore::Draw()
{
    m_SleepAnimation.Draw(m_Bounds.x, m_Bounds.y, 0.0F);
}

void Snore::Draw(float x, float y)
{
    m_SleepAnimation.Draw(m_Bounds.x + x, m_Bounds.y + y, 0.0F);
}

void Snore::Update(float dt)
{
    m_SleepAnimation.Update(dt);

    for (auto it = m_Children.Begin(); it != m_Children.End(); it++)
    {
        (*it)->Update(dt);
    }
}
