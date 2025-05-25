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

#include "Config.h"
#include "controllers/CombatDieController.h"
#include "controllers/Controller.h"
#include "scenes/Character.h"

ControllerState* CombatDieController::Create(const std::string& next)
{
    return new CombatDieController(next);
}

CombatDieController::CombatDieController(const std::string& nextState) :
    ControllerState(nextState)
{
}

void CombatDieController::OnEnter(Controller* controller)
{
    BX_CHECKS(controller != nullptr, "Controller is null");

    Entity* entity = controller->GetEntity();
    if (entity != nullptr)
    {
        auto* character = dynamic_cast<Character*>(entity);
        if (character != nullptr)
        {
            character->PlayAnimation("death", false, true);
        }
    }
}

