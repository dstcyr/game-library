//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MATHS_TWEEN_H
#define MATHS_TWEEN_H

class Tween
{
public:
    static float Linear(float time, float start, float end, float d);
    static float CircularIn(float time, float start, float end, float d);
    static float CircularInOut(float time, float start, float end, float d);
    static float CircularOut(float time, float start, float end, float d);
    static float CubicIn(float time, float start, float end, float d);
    static float CubicInOut(float time, float start, float end, float d);
    static float CubicOut(float time, float start, float end, float d);
    static float ExponentialIn(float time, float start, float end, float d);
    static float ExponentialInOut(float time, float start, float end, float d);
    static float ExponentialOut(float time, float start, float end, float d);
    static float QuadraticIn(float time, float start, float end, float d);
    static float QuadraticInOut(float time, float start, float end, float d);
    static float QuadraticOut(float time, float start, float end, float d);
    static float QuarticIn(float time, float start, float end, float d);
    static float QuarticInOut(float time, float start, float end, float d);
    static float QuarticOut(float time, float start, float end, float d);
    static float QuinticIn(float time, float start, float end, float d);
    static float QuinticInOut(float time, float start, float end, float d);
    static float QuinticOut(float time, float start, float end, float d);
    static float SinusoidalIn(float time, float start, float end, float d);
    static float SinusoidalInOut(float time, float start, float end, float d);
    static float SinusoidalOut(float time, float start, float end, float d);
    static float BackIn(float time, float start, float end, float d);
    static float BackOut(float time, float start, float end, float d);
    static float BackInOut(float time, float start, float end, float d);
    static float BounceIn(float time, float start, float end, float d);
    static float BounceOut(float time, float start, float end, float d);
    static float BounceInOut(float time, float start, float end, float d);
    static float ElasticIn(float time, float start, float end, float d);
    static float ElasticOut(float time, float start, float end, float d);
    static float ElasticInOut(float time, float start, float end, float d);
};

#endif
