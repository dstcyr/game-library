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
#include "controllers/StrollController.h"
#include "controllers/Controller.h"
#include "scenes/Character.h"
#include "maps/TileLayer.h"
#include "maps/Tilemap.h"

ControllerState* StrollController::Create(const std::string& next)
{
    return new StrollController(next);
}

StrollController::StrollController(const std::string& nextState) : ControllerState(nextState)
{
}

void StrollController::OnEnter(Controller* controller)
{
    Entity* tEntity = controller->GetEntity();
    m_Character = dynamic_cast<Character*>(tEntity);
}

void StrollController::OnUpdate(float dt, Controller* controller)
{
    Blackboard* tBB = controller->GetBlackboard();
    bool bMoved = false;
    tBB->moveDirX = 0;
    tBB->moveDirY = 0;
    int choice = MathUtils::RandRange(1, 4);

    if (choice == 1)
    {
        tBB->moveDirX = -1;
        tBB->moveDirY = 0;
        bMoved = true;
        m_Character->PlayAnimation("left", true);
    }
    else if (choice == 2)
    {
        tBB->moveDirX = 1;
        tBB->moveDirY = 0;
        bMoved = true;
        m_Character->PlayAnimation("right", true);
    }
    else if (choice == 3)
    {
        tBB->moveDirX = 0;
        tBB->moveDirY = -1;
        bMoved = true;
        m_Character->PlayAnimation("up", true);
    }
    else if (choice == 4)
    {
        tBB->moveDirX = 0;
        tBB->moveDirY = 1;
        bMoved = true;
        m_Character->PlayAnimation("down", true);
    }

    if (bMoved)
    {
        IWorld& tWorld = Game::Get().World();
        Tilemap* tMap = m_Character->GetParentMap();
        TileLayer* collisions = tMap->GetCollisionLayer();
        if (collisions != nullptr)
        {
            int mapX = 0;
            int mapY = 0;
            m_Character->GetLocalLocation(&mapX, &mapY);
            mapX += tBB->moveDirX;
            mapY += tBB->moveDirY;
            int tX = 0;
            int tY = 0;
            int result = collisions->IsColliding(mapX, mapY, &tX, &tY);
            if (result != 0)
            {
                tBB->moveDirX = 0;
                tBB->moveDirY = 0;
                bMoved = false;
                m_Character->StopAnimation();
            }
            else
            {
                controller->Set(m_NextState);
            }
        }
    }
    else
    {
        m_Character->StopAnimation();
    }
}
