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

#ifndef COMBAT_COMBATTARGET_H
#define COMBAT_COMBATTARGET_H

#include "ICombatState.h"
#include "graphics/SpriteSheet.h"

class CombatScreen;
class CombatActor;

class CombatTarget : public ICombatState
{
public:
    CombatTarget();
    CombatTarget(CombatScreen* screen, CombatActor* actor);

    void Enter() override;
    bool ProcessInput(float deltaTime) override;
    void Update(float deltaTime) override;
    void Draw() override;
    bool IsFinished() override;

private:
    void SelectTarget(CombatActor* target);

    CombatScreen* m_Screen;
    CombatActor* m_Actor;
    std::vector<CombatActor*> m_Targets;
    int m_SelectedIndex = 0;
    std::pair<float, float> m_SelectionLocation;
    SpriteSheet m_Icons;
    bool m_IsFinished = false;
};

#endif
