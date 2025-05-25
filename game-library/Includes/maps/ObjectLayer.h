//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_OBJECTLAYER_H
#define MAPS_OBJECTLAYER_H
//#define DEBUG_OBJECTLAYER

#include "Layer.h"
#include "data/ObjectContainer.h"

class MapPropertyCollection;
class Entity;

class ObjectLayer final : public Layer
{
public:
    bool Load(tinyxml2::XMLNode* nodePtr);
    void Draw() override;
    void PostDraw() override;
    void Clear() override;
    void AddReference(Entity* entity);
    void RemoveReference(size_t id);

private:
    void LoadDefinition(tinyxml2::XMLElement* objectElement, std::vector<MapPropertyCollection>& definitions);
    void CreateInstances(const std::vector<MapPropertyCollection>& definitions);
    static bool CompareEntities(Entity* a, Entity* b);

    ObjectContainer<Entity> m_EntityOnLayer;

#if defined(DEBUG_OBJECTLAYER)
    size_t m_DebugFont = 0;
#endif
};

#endif
