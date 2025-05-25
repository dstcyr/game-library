//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STATS_CHARACTERDEFINITION_H
#define STATS_CHARACTERDEFINITION_H

#include "AttributeSet.h"

struct FCharacterDefinition
{
    std::string name;
    std::string portrait;
    std::string data;
    AttributeSet attributes;
    bool locked = true;

    void TakeDamage(float damage);
    bool IsDead() const;
    std::string ToString();
};

#endif
