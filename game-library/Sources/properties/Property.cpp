//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "properties/Property.h"
#include "save/BufferedFile.h"

void BoolProperty::Save(const std::string& name, BufferedFile* file)
{
    auto typeI = static_cast<uint8_t>(m_Type);
    file->WriteUInt8(typeI);
    file->WriteString(name);
    file->WriteBool(m_Value);
}

void FloatProperty::Save(const std::string& name, BufferedFile* file)
{
    auto typeI = static_cast<uint8_t>(m_Type);
    file->WriteUInt8(typeI);
    file->WriteString(name);
    file->WriteFloat(m_Value);
}

void StringProperty::Save(const std::string& name, BufferedFile* file)
{
    auto typeI = static_cast<uint8_t>(m_Type);
    file->WriteUInt8(typeI);
    file->WriteString(name);
    file->WriteString(m_Value);
}

void IntProperty::Save(const std::string& name, BufferedFile* file)
{
    auto typeI = static_cast<uint8_t>(m_Type);
    file->WriteUInt8(typeI);
    file->WriteString(name);
    file->WriteInt32(m_Value);
}