//  
//     _ ____  ____   ____   ____            _        
//    (_)  _ \|  _ \ / ___| |  _ \ _ __ ___ | |_ ___  
//    | | |_) | |_) | |  _  | |_) | '__/ _ \| __/ _ \ 
//    | |  _ <|  __/| |_| | |  __/| | | (_) | || (_) |
//   _/ |_| \_\_|    \____| |_|   |_|  \___/ \__\___/ 
//  |__/                                              
//  
//  jRPG Prototype
//  Copyright(C) 2024-2025 David St-Cyr
//  
//  The information in this file is confidential and solely for the attention
//  and use of the author. You are hereby notified that any dissemination,
//  distribution or copy of this content is prohibited without the prior
//  written consent of the author.
//
//  David St-Cyr
//  st-cyrdavid@hotmail.com

#ifndef CONTROLLERS_MOVECONTROLLER_H
#define CONTROLLERS_MOVECONTROLLER_H

#include "controllers/ControllerState.h"
#include "controllers/Controller.h"

class Character;

/// <summary>
/// MOVE: The entity transitions to an adjacent tile in a specified direction, smoothly interpolating its position
/// </summary>
class MoveController final : public ControllerState
{
public:
    static ControllerState* Create(const std::string& next);

    explicit MoveController(const std::string& nextState);
    void OnEnter(Controller* controller) override;
    void OnUpdate(float dt, Controller* controller) override;

private:
    Character* m_Character = nullptr;
    float m_CurrentTime = 0.0F;
    float m_TotalTime = 0.2F;
    float m_WorldStartX = 0.0F;
    float m_WorldStartY = 0.0F;
    float m_WorldDestinationX = 0.0F;
    float m_WorldDestinationY = 0.0F;
    int m_OldMapX = 0;
    int m_OldMapY = 0;
};

#endif
