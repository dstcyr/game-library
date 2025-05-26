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

    static float Distance(float x1, float y1, float x2, float y2);

    static float DistanceBetweenRectangles(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
    static bool CheckPointCircle(float px, float py, float cx, float cy, float cr);
    static bool CheckCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);
    static bool CheckPointRect(float px, float py, float rx, float ry, float rw, float rh);
    static bool CheckRects(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
    static bool CheckRects(const Rect<float>& r1, const Rect<float>& r2);
    static bool CheckRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr, float* hitX, float* hitY);
    static bool CheckPointLine(float px, float py, float x1, float y1, float x2, float y2);
    static bool CheckCircleLine(float cx, float cy, float cr, float x1, float y1, float x2, float y2, float* closeX, float* closeY);
    static bool CheckLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* closeX, float* closeY);
    static bool CheckRectLine(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);

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
        (rectA.y + rectA.height) >= rectB.y && rectA.y <= (rectB.y + rectB.height);
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
