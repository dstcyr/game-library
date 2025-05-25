//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "properties/MapPropertyCollection.h"

void MapPropertyCollection::LoadXML(tinyxml2::XMLNode* node)
{
    tinyxml2::XMLNode* tPropNode = node->FirstChild();
    while (tPropNode != nullptr)
    {
        tinyxml2::XMLElement* tParamElement = tPropNode->ToElement();
        const char* tName = tParamElement->Attribute("name");
        const char* tType = tParamElement->Attribute("type");

        if (tName != nullptr)
        {
            std::string tKey = std::string(tName);
            std::string tTypeStr;

            if (tType == nullptr)
            {
                tTypeStr = "string";
            }
            else
            {
                tTypeStr = std::string(tType);
            }

            if (tTypeStr == "bool")
            {
                bool tValue = tParamElement->BoolAttribute("value");
                SetBool(tKey, tValue);
            }
            else if (tTypeStr == "float")
            {
                float tValue = tParamElement->FloatAttribute("value");
                SetFloat(tKey, tValue);
            }
            else if (tTypeStr == "file")
            {
                const char* tFileName = tParamElement->Attribute("value");
                if (tFileName != nullptr)
                {
                    SetString(tKey, tFileName);
                }
            }
            else if (tTypeStr == "int" || tTypeStr == "object")
            {
                int tValue = tParamElement->IntAttribute("value");
                SetInt(tKey, tValue);
            }
            else
            {
                const char* tString = tParamElement->Attribute("value");
                if (tString != nullptr)
                {
                    SetString(tKey, tString);
                }
            }
        }

        tPropNode = tPropNode->NextSibling();
    }
}

void MapPropertyCollection::SetObjectInfo(const std::string& name, const std::string& objectType)
{
    m_ObjectName = name;
    m_ObjectType = objectType;
}

void MapPropertyCollection::SetWorldLocation(float x, float y)
{
    m_WorldX = x;
    m_WorldY = y;
}

void MapPropertyCollection::SetLocalLocation(int x, int y)
{
    m_MapX = x;
    m_MapY = y;
}

void MapPropertyCollection::GetWorldLocation(float* x, float* y) const
{
    *x = m_WorldX;
    *y = m_WorldY;
}

void MapPropertyCollection::GetLocalLocation(int* x, int* y) const
{
    *x = m_MapX;
    *y = m_MapY;
}

bool MapPropertyCollection::IsValid() const
{
    return !m_ObjectType.empty() && !m_ObjectName.empty();
}