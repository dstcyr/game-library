//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "stats/CharacterDefinition.h"

void FCharacterDefinition::TakeDamage(float damage)
{
#if defined(DEBUG_COMBAT)
    BX_LOG(ELogLevel::Log, name + " takes " + std::to_string(damage) + " damages");
#endif

    float damageReceived = MathUtils::Max(0.0F, damage);
    float health = attributes.GetHealth();
    health -= damageReceived;
    if (health < 0.0F)
    {
        health = 0.0F;
    }

    attributes.SetHealth(health);
}

bool FCharacterDefinition::IsDead() const
{
    float health = attributes.GetHealth();
    return health <= 0.0F;
}

std::string FCharacterDefinition::ToString()
{
    return attributes.ToString();
}
