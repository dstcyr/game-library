//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_TILESET_H
#define MAPS_TILESET_H

namespace tinyxml2
{
    class XMLNode;
}

struct FTile
{
    size_t texture = 0;
    Rect<int> source;
};

class Tileset
{
public:
    bool Load(tinyxml2::XMLNode* nodePtr, const std::string& path);
    void Clear();

    FTile* GetTile(int index);
    int GetTileCount() const { return m_TileCount; }
    std::string GetTileType(int index);

private:
    void PrepareTileSources(const std::string& filename);

    std::vector<size_t> m_TextureIds;
    std::map<int, FTile*> m_TileSources;
    std::map<int, std::string> m_TileTypes;
    int m_FirstGID = 0;
    float m_TileWidth = 0;
    float m_TileHeight = 0;
    int m_Spacing = 0;
    int m_Margin = 0;
    int m_TileCount = 0;
    int m_Columns = 0;
};

#endif
