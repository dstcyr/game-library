//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef INPUTS_IINPUT_H
#define INPUTS_IINPUT_H

enum class EKey : unsigned char
{
    EKEY_A = 4,
    EKEY_B = 5,
    EKEY_C = 6,
    EKEY_D = 7,
    EKEY_E = 8,
    EKEY_F = 9,
    EKEY_G = 10,
    EKEY_H = 11,
    EKEY_I = 12,
    EKEY_J = 13,
    EKEY_K = 14,
    EKEY_L = 15,
    EKEY_M = 16,
    EKEY_N = 17,
    EKEY_O = 18,
    EKEY_P = 19,
    EKEY_Q = 20,
    EKEY_R = 21,
    EKEY_S = 22,
    EKEY_T = 23,
    EKEY_U = 24,
    EKEY_V = 25,
    EKEY_W = 26,
    EKEY_X = 27,
    EKEY_Y = 28,
    EKEY_Z = 29,
    EKEY_1 = 30,
    EKEY_2 = 31,
    EKEY_3 = 32,
    EKEY_4 = 33,
    EKEY_5 = 34,
    EKEY_6 = 35,
    EKEY_7 = 36,
    EKEY_8 = 37,
    EKEY_9 = 38,
    EKEY_0 = 39,
    EKEY_RETURN = 40,
    EKEY_ESCAPE = 41,
    EKEY_BACKSPACE = 42,
    EKEY_TAB = 43,
    EKEY_SPACE = 44,
    EKEY_F1 = 58,
    EKEY_F2 = 59,
    EKEY_F3 = 60,
    EKEY_F4 = 61,
    EKEY_F5 = 62,
    EKEY_F6 = 63,
    EKEY_F7 = 64,
    EKEY_F8 = 65,
    EKEY_F9 = 66,
    EKEY_F10 = 67,
    EKEY_F11 = 68,
    EKEY_F12 = 69,
    EKEY_RIGHT = 79,
    EKEY_LEFT = 80,
    EKEY_DOWN = 81,
    EKEY_UP = 82,
};

class IInputs
{
public:
    virtual ~IInputs() = default;

    virtual bool IsKeyDown(EKey key) = 0;
    virtual bool IsKeyPressed(EKey key) = 0;
    virtual bool IsButtonDown(int button) = 0;
    virtual void GetMousePosition(int* x, int* y) = 0;

protected:
    friend class Game;
    virtual void Update() = 0;
};

#endif
