//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "inputs/SdlInputs.h"
#include <SDL.h>

void SdlInputs::Update()
{
    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent) > 0)
    {
        switch (inputEvent.type)
        {
        case SDL_QUIT:
        {
            Game::Get().QuitGame();
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            SDL_MouseButtonEvent buttonDown = inputEvent.button;
            m_MouseStates.at(buttonDown.button) = true;
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            SDL_MouseButtonEvent buttonUp = inputEvent.button;
            m_MouseStates.at(buttonUp.button) = false;
            break;
        }

        case SDL_MOUSEMOTION:
        {
            SDL_MouseMotionEvent motion = inputEvent.motion;
            m_MouseX = motion.x;
            m_MouseY = motion.y;
            break;
        }

        case SDL_KEYUP:
        {
            m_KeyPressed[inputEvent.key.keysym.scancode] = false;
            UpdateKeyboardState();
            break;
        }

        case SDL_KEYDOWN:
        {
            if (inputEvent.key.repeat == 0)
            {
                m_KeyPressed[inputEvent.key.keysym.scancode] = true;
            }

            UpdateKeyboardState();
            break;
        }

        default:
            break;
        }
    }
}

void SdlInputs::UpdateKeyboardState()
{
    int keyCount = 0;
    const Uint8* sdlKeyStates = SDL_GetKeyboardState(&keyCount);
    m_KeyStates.assign(sdlKeyStates, sdlKeyStates + keyCount);
}

bool SdlInputs::IsKeyDown(EKey key)
{
    if (!m_KeyStates.empty())
    {
        auto keyValue = static_cast<unsigned char>(key);
        return (m_KeyStates[keyValue] == 1);
    }

    return false;
}

bool SdlInputs::IsKeyPressed(EKey key)
{
    auto keyValue = static_cast<unsigned char>(key);
    if (m_KeyPressed[keyValue])
    {
        m_KeyPressed[keyValue] = false;
        return true;
    }

    return false;
}

bool SdlInputs::IsButtonDown(int button)
{
    return m_MouseStates.at(button);
}

void SdlInputs::GetMousePosition(int* x, int* y)
{
    *x = m_MouseX;
    *y = m_MouseY;
}
