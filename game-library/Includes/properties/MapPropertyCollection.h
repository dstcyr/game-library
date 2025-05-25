//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef PROPERTIES_MAPPROPERTYCOLLECTION_H
#define PROPERTIES_MAPPROPERTYCOLLECTION_H

#include "PropertyCollection.h"

class BaseLevel;

class MapPropertyCollection : public PropertyCollection
{
public:
    void LoadXML(tinyxml2::XMLNode* node);

    void SetObjectInfo(const std::string& name, const std::string& objectType);
    void SetWorldLocation(float x, float y);
    void SetLocalLocation(int x, int y);
    void GetWorldLocation(float* x, float* y) const;
    void GetLocalLocation(int* x, int* y) const;

    std::string GetObjectName() const { return m_ObjectName; }
    std::string GetObjectType() const { return m_ObjectType; }
    bool IsValid() const;
    void SetParentLevel(BaseLevel* level) { m_ParentLevel = level; }
    BaseLevel* GetParentLevel() const { return m_ParentLevel; }
    int GetIDOnTheMap() const { return m_IDOntheMap; }
    void SetIDOnTheMap(int id) { m_IDOntheMap = id; }

private:
    int m_IDOntheMap = 0;
    std::string m_ObjectName;
    std::string m_ObjectType;
    float m_WorldX = 0.0F;
    float m_WorldY = 0.0F;
    int m_MapX = 0;
    int m_MapY = 0;
    BaseLevel* m_ParentLevel = nullptr;
};

#endif
