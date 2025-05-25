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
#include "combat/CEDebug.h"

CEDebug::CEDebug() :
    CEDebug("", 0.0F)
{
}

CEDebug::CEDebug(std::string text, float countdown) :
    m_Text(std::move(text)),
    m_CountDown(countdown)
{
}

void CEDebug::Execute(CombatEventQueue* eventQueue)
{
    m_Elapsed = 0.0F;
    m_Finish = false;
}

void CEDebug::Update(float deltaTime)
{
    m_Elapsed += deltaTime;
    if (m_Elapsed >= m_Delay)
    {
        BX_LOG(ELogLevel::Log, m_Text);
        m_Finish = true;
    }
}

bool CEDebug::IsFinished()
{
    return m_Finish;
}

float CEDebug::GetCountDown() const
{
    return m_CountDown;
}

void CEDebug::SetCountDown(float countdown)
{
    m_CountDown = countdown;
}

float CEDebug::GetTimePoints(CombatEventQueue* eventQueue)
{
    return -1.0F;
}

std::string CEDebug::GetName()
{
    return m_Text;
}