//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/TileLayer.h"
#include "maps/Tileset.h"
#include "maps/Tilemap.h"

// Bits on the far end of the 32-bit global tile ID are used for tile flags
const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

TileLayer::TileLayer(Tileset* tileset, int tileWidth, int tileHeight) :
    m_Tileset(tileset), 
    m_TileWidth(tileWidth),
    m_TileHeight(tileHeight)
{
}

bool TileLayer::Load(tinyxml2::XMLNode* nodePtr)
{
    tinyxml2::XMLElement* tLayerElement = nodePtr->ToElement();

    const char* tNamePtr = tLayerElement->Attribute("name");
    if (tNamePtr != nullptr)
    {
        m_LayerName = tNamePtr;
    }

    m_Width = tLayerElement->IntAttribute("width");
    m_Height = tLayerElement->IntAttribute("height");

    tinyxml2::XMLNode* tNext = nodePtr->FirstChild();
    while (tNext != nullptr)
    {
        std::string tNextValue = tNext->Value();
        if (tNextValue == "data")
        {
            tinyxml2::XMLElement* tDataElement = tNext->ToElement();
            const char* tEncoding = tDataElement->Attribute("encoding");
            if (tEncoding == nullptr || strcmp(tEncoding, "csv") != 0)
            {
                BX_LOG(ELogLevel::Error, "Only CSV encoding is supported for tilemaps");
                return false;
            }

            const char* tData = tDataElement->GetText();
            ParseTileData(tData);
        }

        tNext = tNext->NextSibling();
    }

    return true;
}

void TileLayer::Draw()
{
    if (m_Tileset->GetTileCount() > 0)
    {
        IGraphics& tGraphic = Game::Get().Graphics();

        int screenW = 0;
        int screenH = 0;
        tGraphic.GetScreenSize(&screenW, &screenH);
        Rect<float> viewport(0.0F, 0.0F, static_cast<float>(screenW + m_TileWidth), static_cast<float>(screenH + m_TileHeight));
        tGraphic.GetCameraLocation(&viewport.x, &viewport.y);

        const auto mapWidth = static_cast<float>(m_Width);
        const auto mapHeight = static_cast<float>(m_Height);
        const auto tileWidth = static_cast<float>(m_TileWidth);
        const auto tileHeight = static_cast<float>(m_TileHeight);

        const auto tFromX = MathUtils::Clamp<float>(viewport.x / tileWidth, 0.0F, mapWidth);
        const auto tFromY = MathUtils::Clamp<float>(viewport.y / tileHeight, 0.0F, mapHeight);
        const auto tToX = MathUtils::Clamp<float>((viewport.x + viewport.width) / tileWidth, tFromX, mapWidth);
        const auto tToY = MathUtils::Clamp<float>((viewport.y + viewport.height) / tileHeight, tFromY, mapHeight);

        const auto tFromViewX = static_cast<int>(tFromX);
        const auto tFromViewY = static_cast<int>(tFromY);
        const auto tToViewX = static_cast<int>(tToX);
        const auto tToViewY = static_cast<int>(tToY);

        if (tFromX >= tToX || tFromY >= tToY)
        {
            return;
        }

        Rect<float> tDest;
        const size_t tDataSize = m_LayerData.size();
        if (tDataSize == 0)
        {
            return;
        }

        for (int y = tFromViewY; y < tToViewY; y++)
        {
            const int tY = y * m_TileHeight;
            for (int x = tFromViewX; x < tToViewX; x++)
            {
                tDest.x = static_cast<float>(x * m_TileWidth);
                tDest.y = static_cast<float>(tY);

                const int tIndex = m_LayerData[y][x]->index;
                if (tIndex <= 0)
                {
                    continue;
                }

                FTile* tTile = m_Tileset->GetTile(tIndex);
                if (tTile == nullptr)
                {
                    continue;
                }

                DrawOriented(y, x, tTile, tDest);
            }
        }
    }
}

void TileLayer::DrawOriented(int y, int x, FTile* tTile, Rect<float>& tDest)
{
    IGraphics& tGraphic = Game::Get().Graphics();
    tDest.width = static_cast<float>(tTile->source.width);
    tDest.height = static_cast<float>(tTile->source.height);

    if (m_LayerData[y][x]->diagonalFlip)
    {
        if (m_LayerData[y][x]->horizontalFlip && m_LayerData[y][x]->verticalFlip)
        {
            tGraphic.DrawImage(tTile->texture, tTile->source, tDest, -90.0F, false, true, 255, 255, 255, 255);
        }
        else if (m_LayerData[y][x]->verticalFlip)
        {
            tGraphic.DrawImage(tTile->texture, tTile->source, tDest, -90.0F, false, false, 255, 255, 255, 255);
        }
        else if (m_LayerData[y][x]->horizontalFlip)
        {
            tGraphic.DrawImage(tTile->texture, tTile->source, tDest, 90.0F, false, false, 255, 255, 255, 255);
        }
        else
        {
            tGraphic.DrawImage(tTile->texture, tTile->source, tDest, -90.0F, true, false, 255, 255, 255, 255);
        }
    }
    else
    {
        tGraphic.DrawImage(tTile->texture, tTile->source, tDest, 0.0F,
            m_LayerData[y][x]->horizontalFlip, m_LayerData[y][x]->verticalFlip, 255, 255, 255, 255);
    }
}

void TileLayer::Clear()
{
    for (auto itr = m_LayerData.begin(); itr != m_LayerData.end(); ++itr)
    {
        for (FTileInfo* tInfo : *itr)
        {
            delete tInfo;
        }
    }

    m_LayerData.clear();
}

int TileLayer::IsColliding(int mapX, int mapY, int* x, int* y)
{
    Rect<float> bounds;
    bounds.Set(
        static_cast<float>(mapX * m_TileWidth),
        static_cast<float>(mapY * m_TileHeight),
        static_cast<float>(m_TileWidth),
        static_cast<float>(m_TileHeight)
    );

    const float halfWidth = bounds.width * 0.5F;
    const float halfHeight = bounds.height * 0.5F;
    bounds.x = bounds.x + halfWidth * 0.5F;
    bounds.y = bounds.y + halfHeight * 0.5F;
    bounds.width = halfWidth;
    bounds.height = halfHeight;
    return IsColliding(bounds, x, y);
}

int TileLayer::IsColliding(const Rect<float>& colliderRect, int* x, int* y)
{
    const int tLeftTile = static_cast<int>(colliderRect.x) / m_TileWidth;
    const int tRightTile = static_cast<int>(colliderRect.x + colliderRect.width) / m_TileWidth;
    const int tTopTile = static_cast<int>(colliderRect.y) / m_TileHeight;
    const int tBottomTile = static_cast<int>(colliderRect.y + colliderRect.height) / m_TileHeight;

    if (tLeftTile >= m_Width || tLeftTile < 0 || tRightTile >= m_Width || tRightTile < 0 ||
        tTopTile >= m_Height || tTopTile < 0 || tBottomTile >= m_Height || tBottomTile < 0 ||
        colliderRect.x < 0 || colliderRect.y < 0)
    {
        return -1;
    }

    for (int i = tLeftTile; i <= tRightTile; i++)
    {
        for (int j = tTopTile; j <= tBottomTile; j++)
        {
            if (i < m_Width && j < m_Height)
            {
                if (m_LayerData[j][i]->index != 0)
                {
                    *x = i;
                    *y = j;
                    return m_LayerData[j][i]->index;
                }
            }
        }
    }

    IWorld& tWorld = Game::Get().World();
    if (m_ParentMap->GetEntityGrid().IsOccupied(tLeftTile, tTopTile))
    {
        *x = tLeftTile;
        *y = tTopTile;
        return 1;
    }

    *x = -1;
    *y = -1;
    return 0;
}

int TileLayer::IsColliding(const Rect<float>& colliderRect)
{
    int tX = 0;
    int tY = 0;
    return IsColliding(colliderRect, &tX, &tY);
}

int TileLayer::IsColliding(int mapX, int mapY)
{
    int tX = 0;
    int tY = 0;
    return IsColliding(mapX, mapY, &tX, &tY);
}

int TileLayer::GetValueAt(int x, int y)
{
    if (x >= m_Width || x < 0 || y >= m_Height || y < 0)
    {
        return -1;
    }

    return m_LayerData[y][x]->index;
}

int TileLayer::IndexAtLocation(int x, int y)
{
    return GetValueAt(x, y);
}

std::vector<Vec2<int>> TileLayer::FindPath(int startX, int startY, int goalX, int goalY)
{
    Vec2<int> start(startX, startY);
    Vec2<int> goal(goalX, goalY);

    std::vector<Vec2<int>> moves = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    struct FPathNode
    {
        Vec2<int> pos;
        int g;
        int f;
        bool operator>(const FPathNode& other) const { return f > other.f; }
    };

    std::priority_queue<FPathNode, std::vector<FPathNode>, std::greater<>> openSet;
    std::unordered_map<Vec2<int>, Vec2<int>, Vec2IntHash> cameFrom;
    std::unordered_map<Vec2<int>, int, Vec2IntHash> gScore;

    openSet.push({ start, 0, Vec2<int>::ManhattanDistance(start, goal) });
    gScore[start] = 0;

    while (!openSet.empty())
    {
        FPathNode current = openSet.top();
        openSet.pop();

        if (current.pos == goal)
        {
            return GeneratePath(goal, cameFrom);
        }

        for (const Vec2<int>& move : moves)
        {
            Vec2<int> neighbor = { current.pos.x + move.x, current.pos.y + move.y };
            if (IsColliding(neighbor.x, neighbor.y) != 0)
            {
                continue;
            }

            int tentativeG = gScore[current.pos] + 1;
            if (gScore.find(neighbor) == gScore.end() || tentativeG < gScore[neighbor])
            {
                cameFrom[neighbor] = current.pos;
                gScore[neighbor] = tentativeG;
                int fScore = tentativeG + Vec2<int>::ManhattanDistance(neighbor, goal);
                openSet.push({ neighbor, tentativeG, fScore });
            }
        }
    }

    return {};
}

std::vector<Vec2<int>> TileLayer::GeneratePath(const Vec2<int>& goal, std::unordered_map<Vec2<int>, Vec2<int>, Vec2IntHash>& cameFrom)
{
    std::vector<Vec2<int>> path;
    Vec2<int> current = goal;

    while (cameFrom.find(current) != cameFrom.end())
    {
        Vec2<int> prev = cameFrom[current];
        if (current.x > prev.x) { path.emplace_back(1, 0); }
        if (current.x < prev.x) { path.emplace_back(-1, 0); }
        if (current.y > prev.y) { path.emplace_back(0, 1); }
        if (current.y < prev.y) { path.emplace_back(0, -1); }
        current = prev;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

void TileLayer::ParseTileData(const char* data)
{
    std::string tCurrentToken;
    std::istringstream tInput(data);

    int tX = 0;
    int tY = 0;

    m_LayerData.emplace_back(m_Width);

    while (std::getline(tInput, tCurrentToken, ','))
    {
        if (!tCurrentToken.empty())
        {
            auto* tInfo = new FTileInfo();

            try
            {
                tInfo->index = std::stoi(tCurrentToken);
                tInfo->horizontalFlip = ((tInfo->index & FLIPPED_HORIZONTALLY_FLAG) != 0U);
                tInfo->verticalFlip = ((tInfo->index & FLIPPED_VERTICALLY_FLAG) != 0U);
                tInfo->diagonalFlip = ((tInfo->index & FLIPPED_DIAGONALLY_FLAG) != 0U);
                tInfo->index &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
            }
            catch (const std::exception& exp)
            {
                BX_LOG(ELogLevel::Error, "Corrupted map detected");
                BX_LOG(ELogLevel::Error, "Error: " + std::string(exp.what()));
            }

            m_LayerData[tY][tX] = tInfo;
            tX++;

            if (tX >= m_Width && tY < m_Height - 1)
            {
                tX = 0;
                tY++;

                m_LayerData.emplace_back(m_Width);
            }
        }
        else
        {
            BX_LOG(ELogLevel::Error, "Invalid map detected");
        }
    }
}
