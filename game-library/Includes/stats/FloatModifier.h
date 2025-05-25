//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STATS_FLOATMODIFIER_H
#define STATS_FLOATMODIFIER_H

#include <cinttypes>

enum class EModifierMode : uint8_t
{
    Percent,
    Add
};

class FloatModifier
{
public:
    FloatModifier();
    explicit FloatModifier(float base);

    void SetBaseValue(float base);
    void AddModifier(float modifier, EModifierMode mode);
    void RemoveModifier(float modifier, EModifierMode mode);
    float GetValue() const;
    float GetBaseValue() const;

private:
    float m_BaseValue;
    float m_PercentModifier;
    float m_AddedModifier;
};

#endif
