//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_TILEMAP_H
#define MAPS_TILEMAP_H

#include "maps/Tileset.h"
#include "maps/Layer.h"
#include "maps/MapTransform.h"
#include "EntityGrid.h"

class Entity;
class ObjectLayer;
class Trigger;
class TileLayer;
class MapPropertyCollection;
class BufferedFile;

namespace tinyxml2
{
    class XMLNode;
    class XMLElement;
}

using TEntityFactory = std::function<Entity* (const MapPropertyCollection&, Tilemap*)>;
using TTriggerFactory = std::function<Trigger* (const MapPropertyCollection&, Tilemap*)>;

class Tilemap
{
public:
    void Update(float deltaTime);
    bool ProcessInput(float deltaTime);
    void Draw();
    bool LoadMap(const std::string& mapName);
    void Clear();
    void AddToObjectLayer(Entity* entity);
    void RemoveFromObjectLayer(Entity* entity);
    Trigger* GetTrigger(int x, int y);
    void Save(BufferedFile* saveFile);
    void Load(BufferedFile* saveFile);
    TileLayer* GetCollisionLayer();
    FMapTransform& GetTransform() { return m_MapTransform; }
    FEntityGrid& GetEntityGrid() { return m_EntityGrid; }


    Entity* FindEntity(int x, int y);
    void DestroyEntity(Entity* entity);
    Entity* CreateEntity(const MapPropertyCollection& definition);


    Trigger* CreateTrigger(const MapPropertyCollection& definition);

    bool IsEntityDefinition(const MapPropertyCollection& definition) const;
    bool IsTriggerDefinition(const MapPropertyCollection& definition) const;

    std::string GetName() const { return m_MapName; }
    std::string GetTileType(int x, int y);


    void RegisterEntityFactory(const std::string& name, TEntityFactory factory);
    void RegisterTriggerFactory(const std::string& name, TTriggerFactory factory);


private:
    static void ParseMapFilename(const std::string& name, std::string& path, std::string& filename);
    void ReadMapSize(const tinyxml2::XMLElement* element);
    bool ReadObjectLayer(tinyxml2::XMLNode* node);
    void ReadTileLayer(tinyxml2::XMLNode* node);

    Tileset m_TileSet;
    FMapTransform m_MapTransform;
    FEntityGrid m_EntityGrid;
    std::map<std::string, Layer*> m_LayersByName;
    std::vector<Layer*> m_LayerDepth;
    ObjectContainer<Entity> m_Instances;
    std::map<int, Trigger*> m_Triggers;
    std::map<std::string, TEntityFactory> m_EntityFactories;
    std::map<std::string, TTriggerFactory> m_TriggerFactories;
    ObjectLayer* m_ObjectsLayer = nullptr;
    std::vector<size_t> m_EntityToDelete;
    std::string m_MapName;
};

#endif
