//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_TILELAYER_H
#define MAPS_TILELAYER_H

#include "maps/Layer.h"
#include "Tileset.h"

namespace tinyxml2
{
    class XMLNode;
}

class Tileset;

struct FTileInfo
{
    int index{ 0 };
    bool horizontalFlip{ false };
    bool verticalFlip{ false };
    bool diagonalFlip{ false };
};

class TileLayer : public Layer
{
public:
    TileLayer(Tileset* tileset, int tileWidth, int tileHeight);
    bool Load(tinyxml2::XMLNode* nodePtr);
    void Draw() override;
    void Clear() override;

    int IsColliding(int mapX, int mapY);
    int IsColliding(int mapX, int mapY, int* x, int* y);
    int IsColliding(const Rect<float>& colliderRect, int* x, int* y);
    int IsColliding(const Rect<float>& colliderRect);

    int GetValueAt(int x, int y);

    int IndexAtLocation(int x, int y) override;

    std::vector<Vec2<int>> FindPath(int startX, int startY, int goalX, int goalY);


private:
    void ParseTileData(const char* data);

    static std::vector<Vec2<int>> GeneratePath(const Vec2<int>& goal, std::unordered_map<Vec2<int>, Vec2<int>, Vec2IntHash>& cameFrom);
    void DrawOriented(int y, int x, FTile* tTile, Rect<float>& tDest);

    Tileset* m_Tileset = nullptr;
    std::vector<std::vector<FTileInfo*>> m_LayerData;
    int m_Width = 0;
    int m_Height = 0;
    int m_TileWidth = 0;
    int m_TileHeight = 0;
};

#endif
