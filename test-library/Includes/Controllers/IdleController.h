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

#ifndef CONTROLLERS_IDLECONTROLLER_H
#define CONTROLLERS_IDLECONTROLLER_H

#include "controllers/ControllerState.h"

class Character;

/// <summary>
/// IDLE: The entity remains inactive for a set duration before transitioning to the next state
/// </summary>
class IdleController final : public ControllerState
{
public:
    static ControllerState* Create(const std::string& next);

    explicit IdleController(const std::string& nextState);
    void OnEnter(Controller* controller) override;
    void OnUpdate(float dt, Controller* controller) override;

private:
    float m_Duration = 0.0F;
    float m_Elapsed = 0.0F;
    int m_MinWaitTime = 0;
    int m_MaxWaitTime = 0;
};

#endif
