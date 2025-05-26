//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MATHS_VEC2_H
#define MATHS_VEC2_H
#include <cmath>
#include "MathUtils.h"

template <typename T>
class Vec2
{
public:
    virtual ~Vec2() = default;

    Vec2()
    {
        Set(0, 0);
    }

    Vec2(T x, T y)
    {
        Set(x, y);
    }

    void Set(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    void Set(const Vec2& other)
    {
        Set(other.x, other.y);
    }

    bool operator==(const Vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const
    {
        return x != other.x || y != other.y;
    }

    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    Vec2 operator+(const Vec2& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator-(const Vec2& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2 operator*(T scalar) const
    {
        return { x * scalar, y * scalar };
    }

    Vec2 operator/(T scalar) const
    {
        return { x / scalar, y / scalar };
    }

    Vec2 operator*(const Vec2& other) const
    {
        return { x * other.x, y * other.y };
    }

    Vec2& operator*=(const Vec2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vec2 operator/(const Vec2& other) const
    {
        return { x / other.x, y / other.y };
    }

    Vec2& operator/=(const Vec2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vec2 operator-() const
    {
        return { -x, -y };
    }

    bool operator<=(const Vec2& other) const
    {
        if (x <= other.x && y <= other.y)
        {
            return true;
        }

        return false;
    }

    bool operator>=(const Vec2& other) const
    {
        if (x >= other.x && y >= other.y)
        {
            return true;
        }

        return false;
    }

    Vec2& operator*=(T scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vec2& operator/=(T scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    std::string ToString() const
    {
        return "{x = " + std::to_string(x) + ", y = " + std::to_string(y) + "}";
    }

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    float Distance(const Vec2& other)
    {
        float diffX = x - other.x;
        float diffY = y - other.y;
        float tLen = diffX * diffX + diffY * diffY;
        return std::sqrtf(tLen);
    }

    float Distance(float x1, float y1, float x2, float y2)
    {
        float diffX = x2 - x1;
        float diffY = y2 - y1;
        float tLen = diffX * diffX + diffY * diffY;
        return std::sqrtf(tLen);
    }

    void Normalize()
    {
        float invLen = 1.0f / Length();
        x *= invLen;
        y *= invLen;
    }

    Vec2 GetNormalized() const
    {
        Vec2 other = *this;
        other.Normalize();
        return other;
    }

    void CW()
    {
        x = x;
        y = -y;
    }

    void CCW()
    {
        x = -x;
        y = y;
    }

    void Reverse()
    {
        x = -x;
        y = -y;
    }

    void South()
    {
        x = 0.0f;
        y = std::abs(y);
    }

    void East()
    {
        x = std::abs(x);
        y = 0.0f;
    }

    void West()
    {
        x = -std::abs(x);
        y = 0.0f;
    }

    void North()
    {
        x = 0.0f;
        y = -std::abs(y);
    }

    void SouthEast()
    {
        x = std::abs(x);
        y = std::abs(y);
    }

    void SouthWest()
    {
        x = -std::abs(x);
        y = std::abs(y);
    }

    void NorthEast()
    {
        x = std::abs(x);
        y = -std::abs(y);
    }

    void NorthWest()
    {
        x = -std::abs(x);
        y = -std::abs(y);
    }

    void Rotate(float angle)
    {
        float len = Length();
        Vec2 normal = GetNormalized();
        float s = std::sinf(angle);
        float c = std::cosf(angle);
        float x = normal.x;
        float y = normal.y;
        normal.x = x * c - y * s;
        normal.y = y * c + x * s;
        *this = normal * len;
    }

    Vec2 GetRotated(float angle) const
    {
        float s = std::sinf(angle);
        float c = std::cosf(angle);
        return { x * c - y * s, y * c + x * s };
    }

    void SetRotation(float angle)
    {
        float angleInRadians = angle * MathUtils::PI / 180.0f;
        float magnitude = Length();
        x = magnitude * std::cosf(angleInRadians);
        y = magnitude * std::sinf(angleInRadians);
    }

    float GetAngle() const
    {
        return (std::atan2f(y, x) / MathUtils::PI) * 180.0f;
    }

    float Dot(const Vec2& a, const Vec2& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    float Dot(const Vec2& other)
    {
        return x * other.x + y * other.y;
    }

    static int ManhattanDistance(const Vec2<int>& a, const Vec2<int>& b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    T x;
    T y;
};

struct Vec2IntHash
{
    size_t operator()(const Vec2<int>& v) const
    {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

#endif
