//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "stats/FloatModifier.h"

FloatModifier::FloatModifier() :
    m_BaseValue(0.0F),
    m_PercentModifier(0.0F),
    m_AddedModifier(0.0F)
{
}

FloatModifier::FloatModifier(float base) :
    m_BaseValue(base),
    m_PercentModifier(0.0F),
    m_AddedModifier(0.0F)
{
}

void FloatModifier::SetBaseValue(float base)
{
    m_BaseValue = base;
}

void FloatModifier::AddModifier(float modifier, EModifierMode mode)
{
    if (mode == EModifierMode::Add)
    {
        m_AddedModifier += modifier;
    }
    else
    {
        m_PercentModifier += modifier;
    }
}

void FloatModifier::RemoveModifier(float modifier, EModifierMode mode)
{
    if (mode == EModifierMode::Add)
    {
        m_AddedModifier -= modifier;
    }
    else
    {
        m_PercentModifier -= modifier;
    }
}

float FloatModifier::GetValue() const
{
    return (m_BaseValue + m_AddedModifier) * (1 + m_PercentModifier);
}

float FloatModifier::GetBaseValue() const
{
    return m_BaseValue;
}
