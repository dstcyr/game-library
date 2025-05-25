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
#include "controllers/WaitController.h"
#include "controllers/Controller.h"
#include "scenes/Character.h"
#include "maps/TileLayer.h"
#include "triggers/Trigger.h"
#include "maps/Tilemap.h"

ControllerState* WaitController::Create(const std::string& next)
{
    return new WaitController(next);
}

WaitController::WaitController(const std::string& nextState) : ControllerState(nextState)
{
}

void WaitController::OnEnter(Controller* controller)
{
    Entity* tEntity = controller->GetEntity();
    m_Owner = dynamic_cast<Character*>(tEntity);
}

void WaitController::OnUpdate(float dt, Controller* controller)
{
    if (m_Moved)
    {
        Entity* tEntity = controller->GetEntity();
        Tilemap* tMap = tEntity->GetParentMap();
        Blackboard* tBB = controller->GetBlackboard();

        TileLayer* collisions = tMap->GetCollisionLayer();
        if (collisions != nullptr)
        {
            int mapX = 0;
            int mapY = 0;
            m_Owner->GetLocalLocation(&mapX, &mapY);
            mapX += tBB->moveDirX;
            mapY += tBB->moveDirY;

            int tX = 0;
            int tY = 0;
            int result = collisions->IsColliding(mapX, mapY, &tX, &tY);
            if (result != 0)
            {
                tBB->moveDirX = 0;
                tBB->moveDirY = 0;
                m_Moved = false;
                m_Owner->StopAnimation();
            }
            else
            {
                controller->Set(m_NextState);
            }
        }
    }
    else
    {
        m_Owner->StopAnimation();
    }
}

bool WaitController::OnProcessInput(float dt, Controller* controller)
{
    IWorld& tWorld = Game::Get().World();
    IInputs& tInput = Game::Get().Inputs();
    Blackboard* tBB = controller->GetBlackboard();
    m_Moved = false;
    tBB->moveDirX = 0;
    tBB->moveDirY = 0;

    Entity* tEntity = controller->GetEntity();
    Tilemap* tMap = tEntity->GetParentMap();

    if (tInput.IsKeyDown(EKey::EKEY_LEFT) || tInput.IsKeyDown(EKey::EKEY_A))
    {
        tBB->moveDirX = -1;
        tBB->moveDirY = 0;
        m_Moved = true;
        m_Owner->PlayAnimation("left", true);
    }
    else if (tInput.IsKeyDown(EKey::EKEY_RIGHT) || tInput.IsKeyDown(EKey::EKEY_D))
    {
        tBB->moveDirX = 1;
        tBB->moveDirY = 0;
        m_Moved = true;
        m_Owner->PlayAnimation("right", true);
    }
    else if (tInput.IsKeyDown(EKey::EKEY_UP) || tInput.IsKeyDown(EKey::EKEY_W))
    {
        tBB->moveDirX = 0;
        tBB->moveDirY = -1;
        m_Moved = true;
        m_Owner->PlayAnimation("up", true);
    }
    else if (tInput.IsKeyDown(EKey::EKEY_DOWN) || tInput.IsKeyDown(EKey::EKEY_S))
    {
        tBB->moveDirX = 0;
        tBB->moveDirY = 1;
        m_Moved = true;
        m_Owner->PlayAnimation("down", true);
    }
    else if (tInput.IsKeyPressed(EKey::EKEY_E))
    {
        int faceX = 0;
        int faceY = 0;
        tMap->GetTransform().GetFacingTile(controller->GetEntity(), &faceX, &faceY);
        Trigger* useTrigger = tMap->GetTrigger(faceX, faceY);
        if (useTrigger != nullptr)
        {
            useTrigger->OnUse(controller->GetEntity());
        }
        else
        {
            Entity* entity = tMap->FindEntity(faceX, faceY);
            if (entity != nullptr)
            {
                entity->Interact();
            }
        }
    }

    return true;
}
