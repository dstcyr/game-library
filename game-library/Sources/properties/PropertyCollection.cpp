//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "save/BufferedFile.h"
#include "properties/Property.h"
#include "properties/PropertyCollection.h"

void PropertyCollection::Save(BufferedFile* file)
{
    if (file == nullptr)
    {
        return;
    }

    auto count = static_cast<int32_t>(m_PropertyMap.size());
    file->WriteInt32(count);

    for (auto it = m_PropertyMap.begin(); it != m_PropertyMap.end(); it++)
    {
        const std::string propName = it->first;
        it->second->Save(propName, file);
    }
}

void PropertyCollection::Load(BufferedFile* file)
{
    if (file == nullptr)
    {
        return;
    }

    Clear();

    int32_t count = 0;
    file->ReadInt32(&count);
    for (int i = 0; i < count; i++)
    {
        uint8_t typeInt = 0;
        file->ReadUInt8(&typeInt);
        auto type = static_cast<EPropertyType>(typeInt);

        std::string propName;
        file->ReadString(propName);

        switch (type)
        {
        case EPropertyType::PT_BOOL:
        {
            bool boolValue = false;
            file->ReadBool(&boolValue);
            SetBool(propName, boolValue);
        }
        break;

        case EPropertyType::PT_FLOAT:
        {
            float floatValue = 0.0F;
            file->ReadFloat(&floatValue);
            SetFloat(propName, floatValue);
        }
        break;

        case EPropertyType::PT_INT:
        {
            int intValue = 0;
            file->ReadInt32(&intValue);
            SetInt(propName, intValue);
        }
        break;

        case EPropertyType::PT_STRING:
        {
            std::string stringValue;
            file->ReadString(stringValue);
            SetString(propName, stringValue);
        }
        break;
        }
    }
}

bool PropertyCollection::GetBool(const std::string& name, bool defaultValue) const
{
    auto it = m_PropertyMap.find(name);
    if (it != m_PropertyMap.end())
    {
        auto* propPtr = it->second;
        if (propPtr != nullptr)
        {
            EPropertyType type = propPtr->GetType();
            if (type == EPropertyType::PT_BOOL)
            {
                auto* boolPtr = dynamic_cast<BoolProperty*>(propPtr);
                if (boolPtr != nullptr)
                {
                    return boolPtr->GetValue();
                }
            }
        }
    }

    return defaultValue;
}

int PropertyCollection::GetInt(const std::string& name, int defaultValue) const
{
    auto it = m_PropertyMap.find(name);
    if (it != m_PropertyMap.end())
    {
        auto* propPtr = it->second;
        if (propPtr != nullptr)
        {
            EPropertyType type = propPtr->GetType();
            if (type == EPropertyType::PT_INT)
            {
                auto* intPtr = dynamic_cast<IntProperty*>(propPtr);
                if (intPtr != nullptr)
                {
                    return intPtr->GetValue();
                }
            }
        }
    }

    return defaultValue;
}

float PropertyCollection::GetFloat(const std::string& name, float defaultValue) const
{
    auto it = m_PropertyMap.find(name);
    if (it != m_PropertyMap.end())
    {
        auto* propPtr = it->second;
        if (propPtr != nullptr)
        {
            EPropertyType type = propPtr->GetType();
            if (type == EPropertyType::PT_FLOAT)
            {
                auto* floatPtr = dynamic_cast<FloatProperty*>(propPtr);
                if (floatPtr != nullptr)
                {
                    return floatPtr->GetValue();
                }
            }
        }
    }

    return defaultValue;
}

std::string PropertyCollection::GetString(const std::string& name, const std::string& defaultValue) const
{
    auto it = m_PropertyMap.find(name);
    if (it != m_PropertyMap.end())
    {
        auto* propPtr = it->second;
        if (propPtr != nullptr)
        {
            EPropertyType type = propPtr->GetType();
            if (type == EPropertyType::PT_STRING)
            {
                auto* stringPtr = dynamic_cast<StringProperty*>(propPtr);
                if (stringPtr != nullptr)
                {
                    return stringPtr->GetValue();
                }
            }
        }
    }

    return defaultValue;
}

bool PropertyCollection::SetBool(const std::string& name, bool value)
{
    if (!Exist(name))
    {
        m_PropertyMap.emplace(name, new BoolProperty(value));
        return true;
    }

    BaseProperty* propPtr = m_PropertyMap[name];
    if (propPtr != nullptr)
    {
        EPropertyType type = propPtr->GetType();
        if (type != EPropertyType::PT_BOOL)
        {
            return false;
        }

        auto* boolPtr = dynamic_cast<BoolProperty*>(propPtr);
        if (boolPtr != nullptr)
        {
            boolPtr->SetValue(value);
            return true;
        }
    }

    return false;
}

bool PropertyCollection::SetInt(const std::string& name, int value)
{
    if (!Exist(name))
    {
        m_PropertyMap.emplace(name, new IntProperty(value));
        return true;
    }

    BaseProperty* propPtr = m_PropertyMap[name];
    if (propPtr != nullptr)
    {
        EPropertyType type = propPtr->GetType();
        if (type != EPropertyType::PT_INT)
        {
            return false;
        }

        auto* intPtr = dynamic_cast<IntProperty*>(propPtr);
        if (intPtr != nullptr)
        {
            intPtr->SetValue(value);
            return true;
        }
    }

    return false;
}

bool PropertyCollection::SetFloat(const std::string& name, float value)
{
    if (!Exist(name))
    {
        m_PropertyMap.emplace(name, new FloatProperty(value));
        return true;
    }

    BaseProperty* propPtr = m_PropertyMap[name];
    if (propPtr != nullptr)
    {
        EPropertyType type = propPtr->GetType();
        if (type != EPropertyType::PT_FLOAT)
        {
            return false;
        }

        auto* floatPtr = dynamic_cast<FloatProperty*>(propPtr);
        if (floatPtr != nullptr)
        {
            floatPtr->SetValue(value);
            return true;
        }
    }

    return false;
}

bool PropertyCollection::SetString(const std::string& name, const std::string& value)
{
    if (!Exist(name))
    {
        m_PropertyMap.emplace(name, new StringProperty(value));
        return true;
    }

    BaseProperty* propPtr = m_PropertyMap[name];
    if (propPtr != nullptr)
    {
        EPropertyType type = propPtr->GetType();
        if (type != EPropertyType::PT_STRING)
        {
            return false;
        }

        auto* strPtr = dynamic_cast<StringProperty*>(propPtr);
        if (strPtr != nullptr)
        {
            strPtr->SetValue(value);
            return true;
        }
    }

    return false;
}

void PropertyCollection::Clear()
{
    for (auto i = m_PropertyMap.begin(); i != m_PropertyMap.end(); ++i)
    {
        delete i->second;
    }

    m_PropertyMap.clear();
}

bool PropertyCollection::Exist(const std::string& name)
{
    return m_PropertyMap.count(name) > 0;
}

EPropertyType PropertyCollection::GetType(const std::string& name)
{
    if (!Exist(name))
    {
        return EPropertyType::PT_ERROR;
    }

    return m_PropertyMap[name]->GetType();
}