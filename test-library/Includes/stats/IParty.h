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

#ifndef STATS_IPARTY_H
#define STATS_IPARTY_H

#include "stats/CharacterDefinition.h"

class IParty
{
public:
    virtual ~IParty() = default;

    virtual void Initialize() = 0;
    virtual std::vector<FCharacterDefinition*> GetPartyDefinition() = 0;
    virtual void UnlockCharacter(const std::string& name) = 0;
    virtual void TakeDamage(const std::string& name, float damage) = 0;
    virtual void Heal(const std::string& name, float damage) = 0;
    virtual void GainXp(int xp) = 0;
};

#endif
