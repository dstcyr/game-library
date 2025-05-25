//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MATHS_RECT_H
#define MATHS_RECT_H

template <typename T>
class Rect
{
public:
    virtual ~Rect() = default;

    Rect()
    {
        Set(0, 0, 0, 0);
    }

    Rect(T x, T y, T w, T h)
    {
        Set(x, y, w, h);
    }

    void Set(T x, T y, T w, T h)
    {
        this->x = x;
        this->y = y;
        this->width = w;
        this->height = h;
    }

    void Set(const Rect& other)
    {
        Set(other.x, other.y, other.width, other.height);
    }

    void GetCenter(T* cx, T* cy)
    {
        *cx = x + width / 2;
        *cy = y + height / 2;
    }

    std::string ToString()
    {
        return std::string("[x:") + std::to_string(x) + ", y:" + 
            std::to_string(y) + ", width:" + std::to_string(width) + ", height:" + std::to_string(height) + " ]";
    }

    T x;
    T y;
    T width;
    T height;
};

#endif
