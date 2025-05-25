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

#ifndef CONTROLLERS_REACHCONTROLLER_H
#define CONTROLLERS_REACHCONTROLLER_H

#include "controllers/ControllerState.h"

class Character;

/// <summary>
/// REACH: The entity uses A* to find a patch and reach the destination
/// </summary>
class ReachController final : public ControllerState
{
public:
    static ControllerState* Create(const std::string& next);

    explicit ReachController(const std::string& nextState);
    void OnEnter(Controller* controller) override;
    void OnUpdate(float dt, Controller* controller) override;

private:
    Character* m_Hero = nullptr;

    std::vector<Vec2<int>> m_Path;
    float m_DestinationX = 0.0F;
    float m_DestinationY = 0.0F;
    bool m_MouseButtonDown = false;
};

#endif
