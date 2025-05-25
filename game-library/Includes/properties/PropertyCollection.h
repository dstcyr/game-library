//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef PROPERTIES_PROPERTYCOLLECTION_H
#define PROPERTIES_PROPERTYCOLLECTION_H

#include "Property.h"

class BufferedFile;
class BaseProperty;

class PropertyCollection
{
public:
    virtual ~PropertyCollection() = default;
    virtual void Save(BufferedFile* file);
    virtual void Load(BufferedFile* file);

    bool GetBool(const std::string& name, bool defaultValue = false) const;
    int GetInt(const std::string& name, int defaultValue = 0) const;
    float GetFloat(const std::string& name, float defaultValue = 0.0F) const;
    std::string GetString(const std::string& name, const std::string& defaultValue = "") const;

    bool SetBool(const std::string& name, bool value);
    bool SetInt(const std::string& name, int value);
    bool SetFloat(const std::string& name, float value);
    bool SetString(const std::string& name, const std::string& value);

    void Clear();
    bool Exist(const std::string& name);
    EPropertyType GetType(const std::string& name);

private:
    std::map<std::string, BaseProperty*> m_PropertyMap;
};

#endif
