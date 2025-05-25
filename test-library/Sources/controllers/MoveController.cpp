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
#include "controllers/MoveController.h"
#include "scenes/Character.h"
#include "maths/Tween.h"
#include "triggers/Trigger.h"
#include "maps/Tilemap.h"

ControllerState* MoveController::Create(const std::string& next)
{
    return new MoveController(next);
}

MoveController::MoveController(const std::string& nextState) : ControllerState(nextState)
{
}

void MoveController::OnEnter(Controller* controller)
{
    int mapX = 0;
    int mapY = 0;
    float entityW = 0.0F;
    float entityH = 0.0F;
    Entity* tEntity = controller->GetEntity();
    m_Character = dynamic_cast<Character*>(tEntity);

    Blackboard* tBB = controller->GetBlackboard();
    if (tEntity == nullptr || tBB == nullptr) { return; }

    tEntity->GetSize(&entityW, &entityH);
    tEntity->GetLocalLocation(&mapX, &mapY);
    tEntity->GetWorldLocation(&m_WorldStartX, &m_WorldStartY);
    m_OldMapX = mapX;
    m_OldMapY = mapY;
    mapX += tBB->moveDirX;
    mapY += tBB->moveDirY;
    tEntity->SetLocalLocation(mapX, mapY);

    Tilemap* tileMap = tEntity->GetParentMap();
    tileMap->GetTransform().GetTileFoot(mapX, mapY, &m_WorldDestinationX, &m_WorldDestinationY, entityW, entityH);
    m_TotalTime = 0.2F;
    m_CurrentTime = 0.0F;
}

void MoveController::OnUpdate(float dt, Controller* controller)
{
    Entity* tEntity = controller->GetEntity();
    if (tEntity == nullptr) { return; }

    m_CurrentTime += dt;
    const float tween = m_CurrentTime / m_TotalTime;
    const float newX = Tween::Linear(m_CurrentTime, m_WorldStartX, m_WorldDestinationX, m_TotalTime);
    const float newY = Tween::Linear(m_CurrentTime, m_WorldStartY, m_WorldDestinationY, m_TotalTime);
    tEntity->SetWorldLocation(newX, newY);

    if (tween >= 1.0F)
    {
        tEntity->SetWorldLocation(m_WorldDestinationX, m_WorldDestinationY);

        IWorld& tWorld = Game::Get().World();

        int mapX = 0;
        int mapY = 0;
        tEntity->GetLocalLocation(&mapX, &mapY);

        Tilemap* tileMap = tEntity->GetParentMap();

        Trigger* trigger = tileMap->GetTrigger(mapX, mapY);
        if (trigger != nullptr)
        {
            trigger->OnEnter(controller->GetEntity());
        }

        Trigger* exitTrigger = tileMap->GetTrigger(m_OldMapX, m_OldMapY);
        if (exitTrigger != nullptr)
        {
            exitTrigger->OnExit(controller->GetEntity());
        }

        controller->Set(m_NextState);
    }
}
