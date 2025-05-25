//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MATHS_MATHUTILS_H
#define MATHS_MATHUTILS_H

class MathUtils
{
public:
    template <class T>
    static T Clamp(T aValue, T aMin, T aMax);

    template <class T>
    static T Min(T aValA, T aValB);

    template <class T>
    static T Max(T aValA, T aValB);

    template <typename T>
    static bool IsColliding(const Rect<T>& rectA, const Rect<T>& rectB);

    template <typename T>
    static bool IsColliding(const Rect<T>& rect, T x, T y);

    static bool NearEqual(float lhs, float rhs);
    static float RandRange(float min, float max);
    static int RandRange(int min, int max);
    static float DistanceBetweenPoints(float p1x, float p1y, float p2x, float p2y);

    static const float PI;
    static const float TwoPI;
    static const float PIOverTwo;
    static const float PIOverFour;
    static const float TO_RADIANS;
    static const float TO_DEGREES;
};

template <typename T>
bool MathUtils::IsColliding(const Rect<T>& rectA, const Rect<T>& rectB)
{
    return rectA.x < (rectB.x + rectB.width) && (rectA.x + rectA.width) > rectB.x &&
        (rectA.y + rectA.h) >= rectB.y && rectA.y <= (rectB.y + rectB.h);
}

template <typename T>
bool MathUtils::IsColliding(const Rect<T>& rect, T x, T y)
{
    return rect.x < x && (rect.x + rect.width) > x && (rect.y + rect.height) >= y && rect.y <= y;
}

template <class T>
T MathUtils::Clamp(const T aValue, const T aMin, const T aMax)
{
    T tValue = aValue;

    if (tValue < aMin)
    {
        tValue = aMin;
    }
    else if (tValue > aMax)
    {
        tValue = aMax;
    }

    return tValue;
}

template <class T>
T MathUtils::Min(const T aValA, const T aValB)
{
    if (aValB < aValA)
    {
        return aValB;
    }

    return aValA;
}

template <class T>
T MathUtils::Max(const T aValA, const T aValB)
{
    if (aValB > aValA)
    {
        return aValB;
    }

    return aValA;
}

#endif
