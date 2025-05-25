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
