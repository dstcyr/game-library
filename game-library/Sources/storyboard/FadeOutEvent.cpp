//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/FadeOutEvent.h"
#include "storyboard/StoryScreenState.h"
#include "storyboard/StoryState.h"

FadeEvent* FadeOutEvent::Create(Storyboard* screen, const std::string& id, bool block)
{
    auto* newEvent = new FadeOutEvent(screen, id, block);
    return newEvent;
}

FadeOutEvent::FadeOutEvent(Storyboard* screen, const std::string& target, bool block) :
    FadeEvent(screen, block),
    m_TargetId(target)
{
    m_FadeAlpha = 0;
    m_Finished = false;
}

void FadeOutEvent::Update(float deltaTime)
{
    // TODO (DaSt):
    /*StoryState* target = dynamic_cast<StoryState*>(m_Screen->Find(m_TargetId));

    if (target != nullptr)
    {
        if (!m_Finished)
        {
            m_Elapsed += deltaTime;
            if (m_Elapsed >= m_FadeSpeed)
            {
                m_Elapsed = 0.0F;
                m_FadeAlpha += m_FadeInc;

                if (m_FadeAlpha >= 255)
                {
                    m_FadeAlpha = 255;
                    m_Finished = true;
                }
            }

            target->SetAlpha(m_FadeAlpha);
        }
    }*/
}
