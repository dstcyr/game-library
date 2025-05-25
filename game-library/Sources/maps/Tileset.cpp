//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/Tileset.h"

bool Tileset::Load(tinyxml2::XMLNode* nodePtr, const std::string& path)
{
    tinyxml2::XMLNode* tImageNode = nodePtr->FirstChild();
    m_FirstGID = nodePtr->ToElement()->IntAttribute("firstgid");

    if (tImageNode != nullptr)
    {
        tinyxml2::XMLElement* tTileElement = nodePtr->ToElement();
        m_TileWidth = tTileElement->FloatAttribute("tilewidth");
        m_TileHeight = tTileElement->FloatAttribute("tileheight");
        m_Spacing = tTileElement->IntAttribute("spacing");
        m_Margin = tTileElement->IntAttribute("margin");
        m_TileCount = tTileElement->IntAttribute("tilecount");
        m_Columns = tTileElement->IntAttribute("columns");

        tinyxml2::XMLNode* tNext = tTileElement->FirstChild();
        while (tNext != nullptr)
        {
            std::string tNextValue = tNext->Value();
            if (tNextValue == "image")
            {
                tinyxml2::XMLElement* tAtlasElement = tNext->ToElement();

                const char* tFilepath = tAtlasElement->Attribute("source");
                if (tFilepath == nullptr)
                {
                    BX_LOG(ELogLevel::Error, "Cannot read tileset image");
                    return false;
                }

                PrepareTileSources(path + std::string(tFilepath));
            }
            else if (tNextValue == "tile")
            {
                tinyxml2::XMLElement* tTileInfoElement = tNext->ToElement();
                int id = tTileInfoElement->IntAttribute("id");
                const char* type = tTileInfoElement->Attribute("type");
                m_TileTypes.emplace(id + m_FirstGID, type);

#if defined(DEBUG_TILE_TYPE)
                BX_LOG(ELogLevel::Log, "Adding " + std::string(type) + " (" + std::to_string(id + m_FirstGID) + ")");
#endif
            }

            tNext = tNext->NextSibling();
        }

        return true;
    }

    BX_LOG(ELogLevel::Error, "Couldn't load tileset");
    return false;
}

void Tileset::Clear()
{
    for (auto itr = m_TileSources.begin(); itr != m_TileSources.end(); ++itr)
    {
        delete itr->second;
    }

    m_TileSources.clear();
}

FTile* Tileset::GetTile(int index)
{
    if (m_TileSources.count(index) > 0)
    {
        return m_TileSources[index];
    }

    return nullptr;
}

std::string Tileset::GetTileType(int index)
{
    if (m_TileTypes.count(index) > 0)
    {
        return m_TileTypes[index];
    }

    return "";
}

void Tileset::PrepareTileSources(const std::string& filename)
{
    const size_t id = Game::Get().Graphics().LoadTexture(filename);
    if (id == 0) { return; }

    m_TextureIds.push_back(id);

    int tTileNumber = m_FirstGID;
    for (int i = 0; i < m_TileCount; i++, tTileNumber++)
    {
        int tY = i / m_Columns;
        int tX = i - tY * m_Columns;

        m_TileSources[tTileNumber] = new FTile();
        m_TileSources[tTileNumber]->texture = id;
        m_TileSources[tTileNumber]->source = {
            tX * static_cast<int>(m_TileWidth),
            tY * static_cast<int>(m_TileHeight),
            static_cast<int>(m_TileWidth),
            static_cast<int>(m_TileHeight)
        };

#if defined(DEBUG_TILE_TYPE)
        if (m_TileTypes.count(i) > 0)
        {
            BX_LOG(ELogLevel::Log, std::to_string(i) + " = " + m_TileTypes[i]);
        }
#endif
    }
}
