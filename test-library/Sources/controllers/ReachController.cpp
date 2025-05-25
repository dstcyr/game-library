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
#include "controllers/ReachController.h"
#include "scenes/Blackboard.h"
#include "controllers/Controller.h"
#include "maps/TileLayer.h"
#include "scenes/Character.h"
#include "maps/Tilemap.h"

ControllerState* ReachController::Create(const std::string& next)
{
    return new ReachController(next);
}

ReachController::ReachController(const std::string& nextState) :
    ControllerState(nextState)
{
}

void ReachController::OnEnter(Controller* controller)
{
    Entity* tEntity = controller->GetEntity();
    m_Hero = dynamic_cast<Character*>(tEntity);

    Blackboard* bb = m_Hero->GetBlackboard();
    int mapX = bb->reachX;
    int mapY = bb->reachY;

    int playerX = 0;
    int playerY = 0;
    m_Hero->GetLocalLocation(&playerX, &playerY);

    Tilemap* tMap = m_Hero->GetParentMap();
    auto* collisions = tMap->GetCollisionLayer();
    if (collisions != nullptr)
    {
        m_Path.clear();
        m_Path = collisions->FindPath(playerX, playerY, mapX, mapY);
    }
}

void ReachController::OnUpdate(float dt, Controller* controller)
{
    IInputs& tInput = Game::Get().Inputs();
    IWorld& tWorld = Game::Get().World();
    IGraphics& tGraphics = Game::Get().Graphics();

    if (!m_Path.empty())
    {
        Vec2<int> tDirection = m_Path[0];
        m_Path.erase(m_Path.begin());

        Blackboard* tBB = controller->GetBlackboard();
        tBB->moveDirX = tDirection.x;
        tBB->moveDirY = tDirection.y;

        if (m_Hero != nullptr)
        {
            if (tBB->moveDirX < 0)
            {
                m_Hero->PlayAnimation("left", true);
            }
            else if (tBB->moveDirX > 0)
            {
                m_Hero->PlayAnimation("right", true);
            }
            else if (tBB->moveDirY < 0)
            {
                m_Hero->PlayAnimation("up", true);
            }
            else if (tBB->moveDirY > 0)
            {
                m_Hero->PlayAnimation("down", true);
            }
        }

        controller->Set(m_NextState);
    }
    else
    {
        if (m_Hero != nullptr)
        {
            m_Hero->StopAnimation();
        }
    }
}
