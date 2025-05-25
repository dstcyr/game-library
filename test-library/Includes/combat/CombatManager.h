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

#ifndef COMBAT_COMBATMANAGER_H
#define COMBAT_COMBATMANAGER_H

#include "ICombat.h"

class CombatManager : public ICombat
{
public:
    static ICombat& Get();

    void Initialize() override;
    void StartCombat() override;
    size_t GetBackgroundImage() const override { return m_BackgroundImage; }

private:
    size_t m_BackgroundImage = 0;
    std::map<std::string, std::string> m_BackgroundMap;
};

#endif
