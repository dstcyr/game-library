//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/Tilemap.h"
#include "maps/TileLayer.h"
#include "maps/ObjectLayer.h"
#include "triggers/Trigger.h"
#include "properties/MapPropertyCollection.h"
#include "scenes/Character.h"
#include "save/BufferedFile.h"

void Tilemap::Update(float deltaTime)
{
    for (auto it = m_Instances.Begin(); it != m_Instances.End(); it++)
    {
        (*it)->Update(deltaTime);
    }

    if (!m_EntityToDelete.empty())
    {
        for (auto it = m_EntityToDelete.begin(); it != m_EntityToDelete.end(); it++)
        {
            size_t id = (*it);
            if (m_Instances.Exists(id))
            {
                if (m_ObjectsLayer != nullptr)
                {
                    m_ObjectsLayer->RemoveReference(id);
                }

                Entity* entity = m_Instances.Find(id);
                if (entity != nullptr)
                {
                    m_Instances.Remove(id);

                    int posX = 0;
                    int posY = 0;
                    entity->GetLocalLocation(&posX, &posY);
                    m_EntityGrid.Clear(posX, posY);

                    entity->Clear();
                    delete entity;
                }
            }
        }

        m_EntityToDelete.clear();
    }
}

bool Tilemap::ProcessInput(float deltaTime)
{
    for (auto it = m_Instances.Begin(); it != m_Instances.End(); it++)
    {
        if (!(*it)->ProcessInput(deltaTime))
        {
            return false;
        }
    }

    return true;
}

void Tilemap::Draw()
{
    for (Layer* layer : m_LayerDepth)
    {
        layer->Draw();
    }

#if defined(SHOW_GRID) || defined(SHOW_ENTITY_GRID)
    IGraphics& tGraphics = Game::Get().Graphics();
#endif

#if defined(SHOW_GRID)
    for (int y = 0; y < m_MapTransform.mapHeight; y++)
    {
        for (int x = 0; x < m_MapTransform.mapWidth; x++)
        {
            float worldX = 0.0F;
            float worldY = 0.0F;
            m_MapTransform.ToWorld(x, y, &worldX, &worldY);
            tGraphics.DrawRect(
                worldX,
                worldY,
                static_cast<float>(m_MapTransform.tileWidth),
                static_cast<float>(m_MapTransform.tileHeight),
                0, 0, 255, 80
            );
        }
    }
#endif

#if defined(SHOW_ENTITY_GRID)
    m_EntityGrid.Draw(m_MapTransform);
#endif

    for (Layer* layer : m_LayerDepth)
    {
        layer->PostDraw();
    }
}

bool Tilemap::LoadMap(const std::string& mapName)
{
    IResources& tResource = Game::Get().Resources();

    tinyxml2::XMLDocument tDoc;
    std::vector<char> xmlFile = tResource.LoadData(mapName);
    if (xmlFile.empty())
    {
        BX_LOG(ELogLevel::Error, mapName + " is empty or not found");
        return false;
    }

    std::string xmlText(xmlFile.begin(), xmlFile.end());
    if (tDoc.Parse(xmlText.c_str()) == tinyxml2::XML_SUCCESS)
    {
        Clear();

        std::string mapPath;
        ParseMapFilename(mapName, mapPath, m_MapName);

        tinyxml2::XMLNode* tNode = tDoc.FirstChild();
        while (tNode != nullptr)
        {
            std::string tNodeValue = tNode->Value();
            if (tNodeValue == "map")
            {
                const tinyxml2::XMLElement* tMapElement = tNode->ToElement();
                ReadMapSize(tMapElement);

                tinyxml2::XMLNode* tMapChild = tNode->FirstChild();
                while (tMapChild != nullptr)
                {
                    std::string tChildValue = tMapChild->Value();
                    if (tChildValue == "tileset")
                    {
                        m_TileSet.Load(tMapChild, mapPath);
                    }
                    else if (tChildValue == "layer")
                    {
                        ReadTileLayer(tMapChild);
                    }
                    else if (tChildValue == "objectgroup")
                    {
                        ReadObjectLayer(tMapChild);
                    }

                    tMapChild = tMapChild->NextSibling();
                }
            }

            tNode = tNode->NextSibling();
        }

        return true;
    }

    BX_LOG(ELogLevel::Error, tDoc.ErrorStr());
    return false;
}

void Tilemap::Clear()
{
    for (auto tItr = m_LayersByName.begin(); tItr != m_LayersByName.end(); ++tItr)
    {
        if (tItr->second != nullptr)
        {
            tItr->second->Clear();
            delete tItr->second;
        }
    }

    for (auto it = m_Triggers.begin(); it != m_Triggers.end(); it++)
    {
        it->second->Clear();
        delete it->second;
    }

    m_EntityGrid.Reset(0);

    m_Triggers.clear();
    m_Instances.Clear();
    m_LayersByName.clear();
    m_LayerDepth.clear();
    m_TileSet.Clear();
    m_EntityGrid.Clear();
    m_ObjectsLayer = nullptr;
}

void Tilemap::ReadTileLayer(tinyxml2::XMLNode* node)
{
    auto* tTileLayer = new TileLayer(&m_TileSet, m_MapTransform.tileWidth, m_MapTransform.tileHeight);
    tTileLayer->SetParentMap(this);

    tinyxml2::XMLElement* tLayerElement = node->ToElement();
    bool tVisible = tLayerElement->BoolAttribute("visible", true);
    if (tTileLayer->Load(node))
    {
        std::string tName = tTileLayer->GetName();
        if (m_LayersByName.count(tName) == 0)
        {
            m_LayersByName.try_emplace(tName, tTileLayer);
            if (tVisible)
            {
                m_LayerDepth.push_back(tTileLayer);
            }
        }
    }
}

bool Tilemap::ReadObjectLayer(tinyxml2::XMLNode* node)
{
    if (m_ObjectsLayer != nullptr)
    {
        BX_LOG(ELogLevel::Warning, "World already has an object layer");
        return false;
    }

    m_ObjectsLayer = new ObjectLayer();
    m_ObjectsLayer->SetParentMap(this);

    if (m_ObjectsLayer->Load(node))
    {
        std::string tName = m_ObjectsLayer->GetName();
        if (m_LayersByName.count(tName) == 0)
        {
            m_LayersByName.emplace(tName, m_ObjectsLayer);
            m_LayerDepth.push_back(m_ObjectsLayer);
            return true;
        }
    }

    BX_LOG(ELogLevel::Error, "Error while reading object layer");
    return false;
}

void Tilemap::ReadMapSize(const tinyxml2::XMLElement* element)
{
    m_MapTransform.mapWidth = element->IntAttribute("width", 0);
    m_MapTransform.mapHeight = element->IntAttribute("height", 0);
    m_MapTransform.tileWidth = element->IntAttribute("tilewidth", 0);
    m_MapTransform.tileHeight = element->IntAttribute("tileheight", 0);
    m_MapTransform.tileHalfWidth = m_MapTransform.tileWidth / 2;
    m_MapTransform.tileHalfHeight = m_MapTransform.tileHeight / 2;

    m_EntityGrid.SetSize(m_MapTransform.mapWidth, m_MapTransform.mapHeight, 0);
}

void Tilemap::ParseMapFilename(const std::string& name, std::string& path, std::string& filename)
{
    const size_t tIdx = name.find_last_of("/\\");
    if (tIdx > 0)
    {
        path = name.substr(0, tIdx + 1);
    }

    size_t lastDot = name.find_last_of('.');
    if (lastDot != std::string::npos)
    {
        filename = name.substr(0, lastDot);
    }
}

TileLayer* Tilemap::GetCollisionLayer()
{
    if (m_LayersByName.count("Collisions") > 0)
    {
        Layer* foundLayer = m_LayersByName["Collisions"];
        return dynamic_cast<TileLayer*>(foundLayer);
    }

    return nullptr;
}

void Tilemap::AddToObjectLayer(Entity* entity)
{
    if (m_ObjectsLayer != nullptr)
    {
        m_ObjectsLayer->AddReference(entity);
    }
}

void Tilemap::RemoveFromObjectLayer(Entity* entity)
{
    if (m_ObjectsLayer != nullptr && entity != nullptr)
    {
        size_t id = entity->GetInstanceID();
        m_ObjectsLayer->RemoveReference(id);
    }
}

Trigger* Tilemap::GetTrigger(int x, int y)
{
    int index = m_MapTransform.GetIndex(x, y);
    if (m_Triggers.count(index) != 0)
    {
        return m_Triggers[index];
    }

    return nullptr;
}

Entity* Tilemap::FindEntity(int x, int y)
{
    for (auto it = m_Instances.Begin(); it != m_Instances.End(); it++)
    {
        int tileX = 0;
        int tileY = 0;
        (*it)->GetLocalLocation(&tileX, &tileY);

        if (tileX == x && tileY == y)
        {
            return *it;
        }
    }

    return nullptr;
}

void Tilemap::DestroyEntity(Entity* entity)
{
    size_t entityID = entity->GetInstanceID();
    m_EntityToDelete.push_back(entityID);
}

Entity* Tilemap::CreateEntity(const MapPropertyCollection& definition)
{
    if (m_ObjectsLayer == nullptr)
    {
        BX_LOG(ELogLevel::Warning, "Creating an entity but there is no object layer");
    }

    std::string objectType = definition.GetObjectType();
    std::transform(objectType.begin(), objectType.end(), objectType.begin(), ::toupper);

    if (m_EntityFactories.count(objectType) > 0)
    {
        Entity* newEntity = m_EntityFactories[objectType](definition, this);
        if (newEntity != nullptr)
        {
            if (m_ObjectsLayer != nullptr)
            {
                m_ObjectsLayer->AddReference(newEntity);
            }

            size_t id = newEntity->GetInstanceID();
            std::string name = newEntity->GetName();
            m_Instances.Add(id, name, newEntity);
            return newEntity;
        }
    }

    return nullptr;
}

Trigger* Tilemap::CreateTrigger(const MapPropertyCollection& definition)
{
    std::string objectType = definition.GetObjectType();
    std::transform(objectType.begin(), objectType.end(), objectType.begin(), ::toupper);

    if (m_TriggerFactories.count(objectType) > 0)
    {
        Trigger* newTrigger = m_TriggerFactories[objectType](definition, this);
        if (newTrigger != nullptr)
        {
            int mapX = 0;
            int mapY = 0;
            definition.GetLocalLocation(&mapX, &mapY);

            int index = m_MapTransform.GetIndex(mapX, mapY);
            m_Triggers.emplace(index, newTrigger);
            return newTrigger;
        }
    }

    return nullptr;
}

bool Tilemap::IsEntityDefinition(const MapPropertyCollection& definition) const
{
    std::string objectType = definition.GetObjectType();
    std::transform(objectType.begin(), objectType.end(), objectType.begin(), ::toupper);
    return m_EntityFactories.count(objectType) > 0;
}

bool Tilemap::IsTriggerDefinition(const MapPropertyCollection& definition) const
{
    std::string objectType = definition.GetObjectType();
    std::transform(objectType.begin(), objectType.end(), objectType.begin(), ::toupper);
    return m_TriggerFactories.count(objectType) > 0;
}

std::string Tilemap::GetTileType(int x, int y)
{
    std::string tileType;
    int selectedIndex = -1;
    for (Layer* layer : m_LayerDepth)
    {
        int index = layer->IndexAtLocation(x, y);
        std::string result = m_TileSet.GetTileType(index);
        if (!result.empty())
        {
            tileType = result;
            selectedIndex = index;
        }
    }

#if defined(DEBUG_TILE_TYPE)
    BX_LOG(ELogLevel::Log, "Tile: " + std::to_string(selectedIndex) + " = " + tileType);
#endif

    return tileType;
}

void Tilemap::Save(BufferedFile* saveFile)
{
    for (auto it = m_Instances.Begin(); it != m_Instances.End(); it++)
    {
        (*it)->Save(saveFile);
    }
}

void Tilemap::Load(BufferedFile* saveFile)
{
    for (auto it = m_Instances.Begin(); it != m_Instances.End(); it++)
    {
        (*it)->Load(saveFile);
    }
}

void Tilemap::RegisterEntityFactory(const std::string& name, TEntityFactory factory)
{
    std::string nameUpper = name;
    std::transform(nameUpper.begin(), nameUpper.end(), nameUpper.begin(), ::toupper);

    if (m_EntityFactories.count(nameUpper) > 0)
    {
        BX_LOG(ELogLevel::Warning, "Entity factory already registered");
        return;
    }

    m_EntityFactories[nameUpper] = std::move(factory);
}

void Tilemap::RegisterTriggerFactory(const std::string& name, TTriggerFactory factory)
{
    std::string nameUpper = name;
    std::transform(nameUpper.begin(), nameUpper.end(), nameUpper.begin(), ::toupper);

    if (m_TriggerFactories.count(nameUpper) > 0)
    {
        BX_LOG(ELogLevel::Warning, "Trigger factory already registered");
        return;
    }

    m_TriggerFactories[nameUpper] = std::move(factory);
}
