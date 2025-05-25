//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_MAPTRANSFORM_H
#define MAPS_MAPTRANSFORM_H

class Entity;

struct FMapTransform
{
    int mapWidth = 0;
    int mapHeight = 0;
    int tileWidth = 0;
    int tileHeight = 0;
    int tileHalfWidth = 0;
    int tileHalfHeight = 0;

    void ToLocal(float worldX, float worldY, int* localX, int* localY) const;
    void ToWorld(int localX, int localY, float* worldX, float* worldY) const;
    void GetCenter(int localX, int localY, float* worldX, float* worldY, float width, float height) const;
    void GetTileFoot(int localX, int localY, float* worldX, float* worldY, float width, float height) const;
    void GetFacingTile(Entity* entity, int* tileX, int* tileY) const;
    int GetIndex(int x, int y) const;
    void GetMapSize(float* width, float* height) const;
    bool IsValidLocation(int x, int y) const;
};

#endif

