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

#ifndef CONTROLLERS_WAITCONTROLLER_H
#define CONTROLLERS_WAITCONTROLLER_H

#include "controllers/ControllerState.h"

class Character;

/// <summary>
/// WAIT: The entity remains idle until receiving player input to move in the specified direction
/// </summary>
class WaitController final : public ControllerState
{
public:
    static ControllerState* Create(const std::string& next);

    explicit WaitController(const std::string& nextState);
    void OnEnter(Controller* controller) override;
    void OnUpdate(float dt, Controller* controller) override;
    bool OnProcessInput(float dt, Controller* controller) override;

private:
    Character* m_Owner = nullptr;
    bool m_Moved = false;
};

#endif
