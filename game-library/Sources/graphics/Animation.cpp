//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

void Animation::Update(float dt)
{
    if (m_Playing)
    {
        m_Elapsed += dt;
        if (m_Elapsed >= m_Delay)
        {
            m_Elapsed = 0.0F;
            m_CurrentFrame++;

            if (m_CurrentFrame > m_LastFrame)
            {
                if (m_Loop)
                {
                    m_CurrentFrame = m_FirstFrame;
                }
                else
                {
                    if (m_HoldLast)
                    {
                        m_CurrentFrame = m_LastFrame;
                    }
                    else
                    {
                        m_CurrentFrame = m_FirstFrame;
                    }

                    m_Playing = false;
                    if (m_OnAnimationEnd)
                    {
                        m_OnAnimationEnd();
                        m_OnAnimationEnd = nullptr;
                    }
                }
            }

            UpdateFrame();
        }
    }
}

void Animation::Init(int frameInRows, int frameWidth, int frameHeight)
{
    m_FrameInRowCount = frameInRows;
    m_FrameWidth = frameWidth;
    m_FrameHeight = frameHeight;

    m_Source.x = 0;
    m_Source.y = 0;
    m_Source.width = m_FrameWidth;
    m_Source.height = m_FrameHeight;

    m_CurrentClip.clear();
}

void Animation::AddClip(const std::string& name, int start, int count, float delay)
{
    //m_Clips.emplace(name, AnimationClip{ start, count, delay });

    if (m_Clips.count(name) == 0)
    {
        AnimationClip ac{};
        ac.start = start;
        ac.count = count;
        ac.delay = delay;

        m_Clips[name] = ac;
    }
}

void Animation::Stop()
{
    SetFrame(m_CurrentClip);
}

void Animation::Play(const std::string& name, bool loop, bool holdLast)
{
    BX_CHECKS(m_Clips.count(name) > 0, "Clip not found for this animation");

    if (!m_Playing || (m_Playing && name != m_CurrentClip))
    {
        UpdateClip(name);
        UpdateFrame();
        m_Playing = true;
    }

    m_Loop = loop;
    m_HoldLast = holdLast;
}

void Animation::PlayOnce(const std::string& name, const std::function<void()>& callback)
{
    m_OnAnimationEnd = callback;
    Play(name, false);
}

void Animation::SetFrame(const std::string& name)
{
    UpdateClip(name);
    UpdateFrame();
    m_Loop = false;
    m_Playing = false;
}

void Animation::UpdateFrame()
{
    const int frameRow = m_CurrentFrame / m_FrameInRowCount;
    const int frameCol = m_CurrentFrame - m_FrameInRowCount * frameRow;
    m_Source.x = m_FrameWidth * frameCol;
    m_Source.y = m_FrameHeight * frameRow;
    m_Source.width = m_FrameWidth;
    m_Source.height = m_FrameHeight;
}

void Animation::UpdateClip(const std::string& name)
{
    const AnimationClip clipInfo = m_Clips[name];
    m_CurrentFrame = clipInfo.start;
    m_FirstFrame = clipInfo.start;
    m_LastFrame = clipInfo.start + clipInfo.count - 1;
    m_Delay = clipInfo.delay;
    m_CurrentClip = name;
}
