//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maths/Tween.h"

float Tween::Linear(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    return c * t / d + b;
}

float Tween::CircularIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    return -c * (std::sqrtf(1 - t * t) - 1) + b;
}

float Tween::CircularInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return -c / 2 * (std::sqrtf(1 - t * t) - 1) + b;
    }

    t -= 2;
    return c / 2 * (std::sqrtf(1 - t * t) + 1) + b;
}

float Tween::CircularOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return c * std::sqrtf(1 - t * t) + b;
}

float Tween::CubicIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t * t + b;
}

float Tween::CubicInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t * t + b;
    }

    t -= 2;
    return c / 2 * (t * t * t + 2) + b;
}

float Tween::CubicOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return c * (t * t * t + 1) + b;
}

float Tween::ExponentialIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    return c * std::powf(2, 10 * (t / d - 1)) + b;
}

float Tween::ExponentialInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * std::powf(2, 10 * (t - 1)) + b;
    }

    t--;
    return c / 2 * (-std::powf(2, -10 * t) + 2) + b;
}

float Tween::ExponentialOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    return c * (-std::powf(2, -10 * t / d) + 1) + b;
}

float Tween::QuadraticIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t + b;
}

float Tween::QuadraticInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t + b;
    }

    t--;
    return -c / 2 * (t * (t - 2) - 1) + b;
}

float Tween::QuadraticOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    return -c * t * (t - 2) + b;
}

float Tween::QuarticIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t * t * t + b;
}

float Tween::QuarticInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t * t * t + b;
    }

    t -= 2;
    return -c / 2 * (t * t * t * t - 2) + b;
}

float Tween::QuarticOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return -c * (t * t * t * t - 1) + b;
}

float Tween::QuinticIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t * t * t * t + b;
}

float Tween::QuinticInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1) 
    {
        return c / 2 * t * t * t * t * t + b;
    }

    t -= 2;
    return c / 2 * (t * t * t * t * t + 2) + b;
}

float Tween::QuinticOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return c * (t * t * t * t * t + 1) + b;
}

float Tween::SinusoidalIn(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    return -c * std::cosf(t / d * (MathUtils::PI / 2)) + c + b;
}

float Tween::SinusoidalInOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    return -c / 2 * (std::cosf(MathUtils::PI * t / d) - 1) + b;
}

float Tween::SinusoidalOut(float time, float start, float end, float d)
{
    float t = MathUtils::Clamp(time, 0.0F, d);
    float c = end - start;
    float b = start;

    return c * std::sinf(t / d * (MathUtils::PI / 2)) + b;
}

float Tween::BackIn(float time, float start, float end, float d)
{
    float s = 1.70158F;
    float postFix = time /= d;
    return end * (postFix)*time * ((s + 1) * time - s) + start;
}

float Tween::BackOut(float time, float start, float end, float d)
{
    float s = 1.70158F;
    return end * ((time = time / d - 1) * time * ((s + 1) * time + s) + 1) + start;
}

float Tween::BackInOut(float time, float start, float end, float d)
{
    float s = 1.70158F;

    time /= d / 2;
    if (time < 1)
    {
        return end / 2 * (time * time * (((s *= (1.525F)) + 1) * time - s)) + start;
    }

    float postFix = time -= 2;
    return end / 2 * ((postFix)*time * (((s *= (1.525F)) + 1) * time + s) + 2) + start;
}

float Tween::BounceIn(float time, float start, float end, float d)
{
    return end - BounceOut(d - time, 0, end, d) + start;
}

float Tween::BounceOut(float time, float start, float end, float d)
{
    time /= d;
    if (time < (1 / 2.75F))
    {
        return end * (7.5625F * time * time) + start;
    }

    if (time < (2 / 2.75F))
    {
        float postFix = time -= (1.5F / 2.75F);
        return end * (7.5625F * (postFix)*time + .75F) + start;
    }

    if (time < (2.5 / 2.75))
    {
        float postFix = time -= (2.25F / 2.75F);
        return end * (7.5625F * (postFix)*time + .9375F) + start;
    }

    float postFix = time -= (2.625F / 2.75F);
    return end * (7.5625F * (postFix)*time + .984375F) + start;
}

float Tween::BounceInOut(float time, float start, float end, float d)
{
    if (time < d / 2)
    {
        return BounceIn(time * 2, 0, end, d) * .5f + start;
    }
    return BounceOut(time * 2 - d, 0, end, d) * .5f + end * .5f + start;
}

float Tween::ElasticIn(float time, float start, float end, float d)
{
    if (time == 0)
    {
        return start;
    }

    time /= d;
    if (time == 1)
    {
        return start + end;
    }

    float p = d * 0.3F;
    float a = end;
    float s = p / 4;
    float postFix = a * powf(2, 10 * (time -= 1)); // this is a fix, again, with post-increment operators
    return -(postFix * sinf((time * d - s) * (2 * MathUtils::PI) / p)) + start;
}

float Tween::ElasticOut(float time, float start, float end, float d)
{
    if (time == 0)
    {
        return start;
    }

    time /= d;
    if (time == 1)
    {
        return start + end;
    }

    float p = d * 0.3F;
    float a = end;
    float s = p / 4;
    return (a * powf(2, -10 * time) * sinf((time * d - s) * (2 * MathUtils::PI) / p) + end + start);
}

float Tween::ElasticInOut(float time, float start, float end, float d)
{
    if (time == 0)
    {
        return start;
    }

    time /= d / 2;
    if (time == 2)
    {
        return start + end;
    }

    float p = d * (0.3F * 1.5F);
    float a = end;
    float s = p / 4;

    if (time < 1)
    {
        float postFix = a * powf(2, 10 * (time -= 1)); // postIncrement is evil
        return -.5f * (postFix * sinf((time * d - s) * (2 * MathUtils::PI) / p)) + start;
    }

    float postFix = a * powf(2, -10 * (time -= 1)); // postIncrement is evil
    return postFix * sinf((time * d - s) * (2 * MathUtils::PI) / p) * .5f + end + start;
}