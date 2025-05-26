//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GRAPHICS_ANIMATION_H
#define GRAPHICS_ANIMATION_H

#include "graphics/Sprite.h"
#include <string>
#include <functional>
#include <map>

struct AnimationClip
{
    int start;
    int count;
    float delay;
};

class Animation final : public Sprite
{
public:
    bool Update(float dt);
    void Init(int frameInRows, int frameWidth, int frameHeight);
    void AddClip(const std::string& name, int start, int count, float delay);
    void Stop();
    void Play(const std::string& name, bool loop, bool holdLast = false);
    void PlayOnce(const std::string& name, const std::function<void()>& callback);
    void SetFrame(const std::string& name);
    const std::string& GetCurrentClipName() const { return m_CurrentClip; }
    bool IsLooping() const { return m_Loop; }

private:
    void UpdateFrame();
    void UpdateClip(const std::string& name);

    std::map<std::string, AnimationClip> m_Clips;
    int m_FrameInRowCount = 0;
    int m_FrameWidth = 0;
    int m_FrameHeight = 0;
    int m_FirstFrame = 0;
    int m_LastFrame = 0;
    float m_Delay = 0.0F;
    float m_Elapsed = 0.0F;
    bool m_Playing = false;
    bool m_Loop = false;
    bool m_HoldLast = false;
    int m_CurrentFrame = 0;
    std::string m_CurrentClip;

    std::function<void()> m_OnAnimationEnd;
};

#endif
