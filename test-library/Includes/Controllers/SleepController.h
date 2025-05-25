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

#ifndef CONTROLLERS_SLEEPCONTROLLER_H
#define CONTROLLERS_SLEEPCONTROLLER_H

#include "controllers/ControllerState.h"
#include <string>
#include "graphics/Animation.h"

class Character;
class Snore;

/// <summary>
/// SLEEP: The entity don't move and play a "ZZZZ" animation
/// </summary>
class SleepController final : public ControllerState
{
public:
    static ControllerState* Create(const std::string& next);

    explicit SleepController(const std::string& nextState);
    void OnEnter(Controller* controller) override;
    void OnUpdate(float dt, Controller* controller) override;

private:
    Character* m_Character = nullptr;
    Entity* m_SleepEntity = nullptr;
};

#endif
