//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GRAPHICS_FADE_H
#define GRAPHICS_FADE_H
#include <functional>

class Fade
{
public:
    void Init(bool startOut);
    void Update(float deltaTime);
    void Draw();
    void FadeIn();
    void FadeIn(const std::function<void()>& callback);
    void FadeOut(bool bHold);
    void FadeOut(const std::function<void()>& callback, bool bHold);
    void SetSpeed(float speed, int inc);

    bool IsFading() const { return m_Fading; }

private:
    void UpdateScreenSize();

    bool m_Fading = false;
    bool m_FadingOut = true;
    float m_FadeSpeed = 0.001F;
    int m_FadeInc = 7;
    int m_FadeAlpha = 255;
    float m_Elapsed = 0.0F;
    bool m_Hold = true;
    float m_ScreenWidth = 0.0F;
    float m_ScreenHeight = 0.0F;

    static std::function<void()> FadeInCallback;
    static std::function<void()> FadeOutCallback;
};

#endif
