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

#ifndef STATS_PARTY_H
#define STATS_PARTY_H

#include "IParty.h"

class Party : public IParty
{
public:
    static IParty& Get();

    void Initialize() override;
    std::vector<FCharacterDefinition*> GetPartyDefinition() override;
    void UnlockCharacter(const std::string& name) override;
    void TakeDamage(const std::string& name, float damage) override;
    void Heal(const std::string& name, float damage) override;
    void GainXp(int xp) override;

private:
    std::map<std::string, FCharacterDefinition> m_MemberMap;
};

#endif
