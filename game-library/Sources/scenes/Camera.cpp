//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "scenes/Camera.h"
#include "maths/Tween.h"
#include "maps/Tilemap.h"

Camera::Camera(size_t instId, const std::string& name) :
    Entity(instId, name)
{
}

void Camera::Update(float deltaTime)
{
    if (m_Follow != nullptr)
    {
        int screenX = 0;
        int screenY = 0;
        float followX = 0.0F;
        float followY = 0.0F;
        float followW = 0.0F;
        float followH = 0.0F;

        IGraphics& tGraphics = Game::Get().Graphics();
        tGraphics.GetScreenSize(&screenX, &screenY);
        m_Follow->GetWorldLocation(&followX, &followY);
        m_Follow->GetSize(&followW, &followH);

        const float newX = followX - (static_cast<float>(screenX) / 2.0F) + (followW / 2.0F);
        const float newY = followY - (static_cast<float>(screenY) / 2.0F) + (followH / 2.0F);
        UpdateCameraLocation(newX, newY);
    }
}

void Camera::Focus(float x, float y)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.GetCameraLocation(&m_SavedLocationX, &m_SavedLocationY);

    UpdateCameraLocation(x, y);
}

void Camera::Restore()
{
    UpdateCameraLocation(m_SavedLocationX, m_SavedLocationY);
}

void Camera::UpdateCameraLocation(float x, float y)
{
    IGraphics& tGraphics = Game::Get().Graphics();
    IWorld& tWorld = Game::Get().World();

    float hLimit = 0.0F;
    float vLimit = 0.0F;
    int screenW = 0;
    int screenH = 0;

    tGraphics.GetScreenSize(&screenW, &screenH);
    m_ParentMap->GetTransform().GetMapSize(&hLimit, &vLimit);

    hLimit = hLimit - static_cast<float>(screenW);
    vLimit = vLimit - static_cast<float>(screenH);

    if (hLimit < 0) { hLimit = 0.0F; }
    if (vLimit < 0) { vLimit = 0.0F; }

    if (x < 0.0F)
    {
        x = 0.0F;
    }
    else
    {
        if (x > hLimit)
        {
            x = hLimit;
        }
    }

    if (y < 0.0F)
    {
        y = 0.0F;
    }
    else
    {
        if (y > vLimit)
        {
            y = vLimit;
        }
    }

    tGraphics.SetCameraLocation(x, y);
}
