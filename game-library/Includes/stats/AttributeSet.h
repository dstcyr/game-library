//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STATS_ATTRIBUTESET_H
#define STATS_ATTRIBUTESET_H

#include "FloatModifier.h"
#include <string>

class AttributeSet
{
public:
    AttributeSet() = default;
    AttributeSet(float health, float magic, float strength, float speed, float intelligence);
    FloatModifier& GetMaxHealthAttribute() { return m_MaxHealth; }
    FloatModifier& GetMaxMagicAttribute() { return m_MaxMagic; }
    FloatModifier& GetStrengthAttribute() { return m_Strength; }
    FloatModifier& GetSpeedAttribute() { return m_Speed; }
    FloatModifier& GetIntelligenceAttribute() { return m_Intelligence; }

    float GetHealth() const { return m_Health; }
    void SetHealth(float health) { m_Health = health; }
    float GetMagic() const { return m_Magic; }
    void SetMagic(float magic) { m_Magic = magic; }
    int GetLevel() const { return m_Level; }
    void SetLevel(int level) { m_Level = level; }
    int GetXp() const { return m_Xp; }
    void AddXp(int xp);
    int NextLevel() const;
    std::string ToString();

private:
    int CalculateMaxHealth() const;

    int m_Level = 1;
    int m_Xp = 0;
    float m_Health = 0.0F;
    float m_Magic = 0.0F;
    FloatModifier m_MaxHealth;
    FloatModifier m_MaxMagic;
    FloatModifier m_Strength;
    FloatModifier m_Speed;
    FloatModifier m_Intelligence;
};

#endif
