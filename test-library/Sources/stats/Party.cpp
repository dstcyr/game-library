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
#include "stats/Party.h"
#include "stats/AttributeSet.h"

IParty& Party::Get()
{
    static Party party;
    return party;
}

void Party::Initialize()
{
    FCharacterDefinition hero = {
        "Zest",
        "textures/hero_portrait.png",
        "characters/combatHero.xml",
        AttributeSet(100.0F, 60.0F, 10.0F, 5.0F, 10.0F),
        false
    };

    FCharacterDefinition thief = {
        "Sauber",
        "textures/thief_portrait.png",
        "characters/combatThief.xml",
        AttributeSet(100.0F, 60.0F, 10.0F, 4.0F, 10.0F),
        false
    };

    FCharacterDefinition mage = {
        "Floe",
        "textures/mage_portrait.png",
        "characters/combatMage.xml",
        AttributeSet(100.0F, 60.0F, 10.0F, 2.0F, 10.0F),
        false
    };

    m_MemberMap.emplace("Zest", hero);
    m_MemberMap.emplace("Sauber", thief);
    m_MemberMap.emplace("Floe", mage);
}

std::vector<FCharacterDefinition*> Party::GetPartyDefinition()
{
    std::vector<FCharacterDefinition*> result;
    for (auto it = m_MemberMap.begin(); it != m_MemberMap.end(); ++it)
    {
        if (!it->second.locked)
        {
            FCharacterDefinition& character = it->second;
            result.push_back(&character);
        }
    }

    return result;
}

void Party::UnlockCharacter(const std::string& name)
{
    if (m_MemberMap.count(name) > 0)
    {
        m_MemberMap[name].locked = false;
    }
}

void Party::TakeDamage(const std::string& name, float damage)
{
    float damageReceived = MathUtils::Max(0.0F, damage);
    if (m_MemberMap.count(name) > 0)
    {
        m_MemberMap[name].TakeDamage(damage);
    }
}

void Party::Heal(const std::string& name, float damage)
{
    float healingReceived = MathUtils::Max(0.0F, damage);
    if (m_MemberMap.count(name) > 0)
    {
        AttributeSet& as = m_MemberMap[name].attributes;
        FloatModifier maxHealth = as.GetMaxHealthAttribute();
        float health = as.GetHealth();
        float maxHealthValue = maxHealth.GetValue();
        health += healingReceived;
        if (health > maxHealthValue)
        {
            health = maxHealthValue;
        }

        as.SetHealth(health);
    }
}

void Party::GainXp(int xp)
{
    for (auto it = m_MemberMap.begin(); it != m_MemberMap.end(); ++it)
    {
        if (!it->second.locked)
        {
            FCharacterDefinition& character = it->second;
            AttributeSet& as = character.attributes;
            as.AddXp(xp);
        }
    }
}
