//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_CAMERA_H
#define SCENES_CAMERA_H

#include "Entity.h"
#include "properties/MapPropertyCollection.h"

class Camera : public Entity
{
public:
    Camera(size_t instId, const std::string& name);
    void Update(float deltaTime) override;

    void SetFollow(Entity* follow) { m_Follow = follow; }
    void SetSpeed(float speed) { m_LerpSpeed = speed; }
    void Focus(float x, float y);
    void Restore();

private:
    void UpdateCameraLocation(float x, float y);

    Entity* m_Follow = nullptr;
    float m_LerpSpeed = 0.2F;
    float m_CurrentTime = 0.0F;

    float m_SavedLocationX = 0.0F;
    float m_SavedLocationY = 0.0F;
};

#endif
