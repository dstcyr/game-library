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
#include "triggers/Trigger.h"
#include "maps/Tilemap.h"
#include "maps/ObjectLayer.h"

bool ObjectLayer::Load(tinyxml2::XMLNode* nodePtr)
{
    IWorld& tWorld = Game::Get().World();

    tinyxml2::XMLElement* tLayerElement = nodePtr->ToElement();

    const char* tNamePtr = tLayerElement->Attribute("name");
    if (tNamePtr != nullptr)
    {
        m_LayerName = tNamePtr;
    }

    std::vector<MapPropertyCollection> definitions;

    tinyxml2::XMLNode* tNext = nodePtr->FirstChild();
    while (tNext != nullptr)
    {
        std::string tNextValue = tNext->Value();
        if (tNextValue == "object")
        {
            tinyxml2::XMLElement* tObjectElement = tNext->ToElement();
            LoadDefinition(tObjectElement, definitions);
        }

        tNext = tNext->NextSibling();
    }

    CreateInstances(definitions);

    for (auto& entityDef : definitions)
    {
        entityDef.Clear();
    }

    definitions.clear();

#if defined(DEBUG_OBJECTLAYER)
    IGraphics& tGraphics = Game::Get().Graphics();
    m_DebugFont = tGraphics.LoadFont("fonts/charriot.ttf", 18);
#endif

    return true;
}

void ObjectLayer::LoadDefinition(tinyxml2::XMLElement* objectElement, std::vector<MapPropertyCollection>& definitions)
{
    IWorld& tWorld = Game::Get().World();

    MapPropertyCollection newDefinition;
    int id = objectElement->IntAttribute("id", -1);
    const char* objectName = objectElement->Attribute("name");
    const char* tType = objectElement->Attribute("type");

    newDefinition.SetObjectInfo(objectName, tType);
    newDefinition.SetIDOnTheMap(id);

    float worldX = objectElement->FloatAttribute("x");
    float worldY = objectElement->FloatAttribute("y");
    newDefinition.SetWorldLocation(worldX, worldY);

    int mapX = 0;
    int mapY = 0;
    m_ParentMap->GetTransform().ToLocal(worldX, worldY, &mapX, &mapY);
    newDefinition.SetLocalLocation(mapX, mapY);

    if (newDefinition.IsValid())
    {
        tinyxml2::XMLNode* tParamNode = objectElement->FirstChild();
        if (tParamNode != nullptr)
        {
            newDefinition.LoadXML(tParamNode);
        }

        definitions.push_back(newDefinition);
    }
}

void ObjectLayer::CreateInstances(const std::vector<MapPropertyCollection>& definitions)
{
    IWorld& tWorld = Game::Get().World();

    for (const auto& entityDef : definitions)
    {
        if (m_ParentMap->IsEntityDefinition(entityDef))
        {
            m_ParentMap->CreateEntity(entityDef);
        }
        else if (m_ParentMap->IsTriggerDefinition(entityDef))
        {
            m_ParentMap->CreateTrigger(entityDef);
        }
        else
        {
            BX_LOG(ELogLevel::Warning, "Definition " + entityDef.GetObjectName() + " is not recognized");
        }
    }
}

void ObjectLayer::Draw()
{
    std::sort(m_EntityOnLayer.Begin(), m_EntityOnLayer.End(), CompareEntities);
    for (auto it = m_EntityOnLayer.Begin(); it != m_EntityOnLayer.End(); it++)
    {
        (*it)->Draw();
    }
}

void ObjectLayer::PostDraw()
{
#if defined(DEBUG_OBJECTLAYER)
    IGraphics& tDebugGraphics = Game::Get().Graphics();
    tDebugGraphics.EnableCamera(false);
    float startY = 70.0F;
    int cnt = 1;
    for (auto it = m_EntityOnLayer.Begin(); it != m_EntityOnLayer.End(); it++)
    {
        std::string entry = "[" + std::to_string(cnt) + "] " + (*it)->GetName();
        entry += " -> " + std::to_string((*it)->GetInstanceID());
        entry += " " + (*it)->GetBounds().ToString();

        tDebugGraphics.DrawString(entry, m_DebugFont, 10.0F, startY, 255, 255, 0, 255);
        startY += 30.0F;
        cnt++;
    }
    tDebugGraphics.EnableCamera(true);
#endif
}

void ObjectLayer::Clear()
{
}

void ObjectLayer::AddReference(Entity* entity)
{
    BX_CHECKS(entity != nullptr, "Trying to add a null entity");

    if (m_EntityOnLayer.Find(entity->GetInstanceID()) != nullptr)
    {
        BX_LOG(ELogLevel::Warning, "Trying to add entity with same id (" + entity->GetName() + ")");
        return;
    }

    m_EntityOnLayer.Add(entity->GetInstanceID(), entity->GetName(), entity);
}

void ObjectLayer::RemoveReference(size_t id)
{
    m_EntityOnLayer.Remove(id);
}

bool ObjectLayer::CompareEntities(Entity* a, Entity* b)
{
    int aX = 0;
    int aY = 0;
    int bX = 0;
    int bY = 0;

    a->GetLocalLocation(&aX, &aY);
    b->GetLocalLocation(&bX, &bY);
    return aY < bY;
}
