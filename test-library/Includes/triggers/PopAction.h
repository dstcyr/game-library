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

#ifndef TRIGGERS_POPACTION_H
#define TRIGGERS_POPACTION_H

#include "triggers/IAction.h"

class Entity;
class Trigger;
class MapPropertyCollection;
class Tilemap;

class PopAction : public IAction
{
public:
    static Trigger* Create(const MapPropertyCollection& definition, Tilemap* map);

    PopAction(int mapX, int mapY);
    void Initialize();
    void Execute(Entity* entity) override;

private:
    void FadeOutComplete();

    int m_TargetX = 0;
    int m_TargetY = 0;
    Entity* m_EntityPtr = nullptr;
};

#endif
