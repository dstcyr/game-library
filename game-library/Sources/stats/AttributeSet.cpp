//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "stats/AttributeSet.h"

AttributeSet::AttributeSet(float health, float magic, float strength, float speed, float intelligence) :
    m_Health(health),
    m_Magic(magic)
{
    m_MaxHealth.SetBaseValue(health);
    m_MaxMagic.SetBaseValue(magic);

    m_Strength.SetBaseValue(strength);
    m_Speed.SetBaseValue(speed);
    m_Intelligence.SetBaseValue(intelligence);
}

void AttributeSet::AddXp(int xp)
{
    int next = NextLevel();
    int xpToAdd = xp;

    while (xpToAdd > 0)
    {
        if (m_Xp + xpToAdd > next)
        {
            int rest = next - m_Xp;
            xpToAdd -= rest;
            m_Xp = 0;
            m_Level++;
            next = NextLevel();

            int newMaxHealth = CalculateMaxHealth();
            m_MaxHealth.SetBaseValue(static_cast<float>(newMaxHealth));
            m_Health = static_cast<float>(newMaxHealth);
        }
        else
        {
            m_Xp += xpToAdd;
            xpToAdd = 0;
        }
    }
}

int AttributeSet::NextLevel() const
{
    double exponent = 1.5;
    double baseXP = 1000.0;
    double nextValue = std::floor(baseXP * std::pow(m_Level, exponent));
    return static_cast<int>(nextValue);
}

std::string AttributeSet::ToString()
{
    float health = GetHealth();
    float maxHealth = m_MaxHealth.GetValue();
    float speed = m_Speed.GetValue();

    return std::string("[HP:" + std::to_string(health) + ", MAXHP:" + std::to_string(maxHealth) + ", SPEED:" + std::to_string(speed));
}

int AttributeSet::CalculateMaxHealth() const
{
    float a = 0.08F;  // Adjust this for fine-tuning
    float b = 2.0F;   // Quadratic term
    float c = 10.0F;  // Linear term
    int d = 100;      // Base health

    a = MathUtils::RandRange(0.05F, 0.09F);
    b = MathUtils::RandRange(2.0F, 4.0F);

    int newHealth = static_cast<int>(a * m_Level * m_Level * m_Level + b * m_Level * m_Level + c * m_Level + d);
    newHealth = (newHealth + 5) / 10 * 10;
    return newHealth;
}
