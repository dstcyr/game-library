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
#include "controllers/IdleController.h"
#include "controllers/Controller.h"
#include "scenes/Character.h"

ControllerState* IdleController::Create(const std::string& next)
{
    return new IdleController(next);
}

IdleController::IdleController(const std::string& nextState) : ControllerState(nextState)
{
}

void IdleController::OnEnter(Controller* controller)
{
    m_Duration = static_cast<float>(MathUtils::RandRange(m_MinWaitTime, m_MaxWaitTime));
    m_Elapsed = 0.0F;
    m_MinWaitTime = 3;
    m_MaxWaitTime = 5;

    Entity* tEntity = controller->GetEntity();
    auto* tCharacter = dynamic_cast<Character*>(tEntity);
    tCharacter->StopAnimation();
}

void IdleController::OnUpdate(float dt, Controller* controller)
{
    m_Elapsed += dt;
    if (m_Elapsed >= m_Duration)
    {
        controller->Set(m_NextState);
    }
}
