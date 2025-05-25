//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/MapTransform.h"

void FMapTransform::ToLocal(float worldX, float worldY, int* localX, int* localY) const
{
    if (tileWidth == 0 || tileHeight == 0)
    {
        *localX = 0;
        *localY = 0;
    }
    else
    {
        *localX = static_cast<int>(worldX) / tileWidth;
        *localY = static_cast<int>(worldY) / tileHeight;
    }
}

void FMapTransform::ToWorld(int localX, int localY, float* worldX, float* worldY) const
{
    *worldX = static_cast<float>(localX * tileWidth);
    *worldY = static_cast<float>(localY * tileHeight);
}

void FMapTransform::GetCenter(int localX, int localY, float* worldX, float* worldY, float width, float height) const
{
    float wX = 0.0F;
    float wY = 0.0F;
    ToWorld(localX, localY, &wX, &wY);

    *worldX = (wX + static_cast<float>(tileHalfWidth)) - (width / 2.0F);
    *worldY = (wY + static_cast<float>(tileHalfHeight)) - (height / 2.0F);
}


void FMapTransform::GetTileFoot(int localX, int localY, float* worldX, float* worldY, float width, float height) const
{
    float wX = static_cast<float>(localX * tileWidth) + tileHalfWidth;
    float wY = static_cast<float>(localY * tileHeight) + tileHalfHeight;

    float newX = wX - width / 2.0F;
    float newY = (wY - height / 2.0F) + (tileHeight / 2.0F) - (height / 2.0F);

    *worldX = newX;
    *worldY = newY;
}

void FMapTransform::GetFacingTile(Entity* entity, int* tileX, int* tileY) const
{
    float worldX = 0.0F;
    float worldY = 0.0F;
    int localX = 0;
    int localY = 0;
    int incX = 0;
    int incY = 0;

    entity->GetCenter(&worldX, &worldY);
    ToLocal(worldX, worldY, &localX, &localY);

    const EDirection direction = entity->GetDirection();
    switch (direction)
    {
    case EDirection::e_Left:
        incX = -1;
        break;

    case EDirection::e_Right:
        incX = 1;
        break;

    case EDirection::e_Up:
        incY = -1;
        break;

    case EDirection::e_Down:
        incY = 1;
        break;
    }

    *tileX = localX + incX;
    *tileY = localY + incY;
}

int FMapTransform::GetIndex(int x, int y) const
{
    return x + y * mapWidth;
}

void FMapTransform::GetMapSize(float* width, float* height) const
{
    *width = static_cast<float>(mapWidth * tileWidth);
    *height = static_cast<float>(mapHeight * tileHeight);
}

bool FMapTransform::IsValidLocation(int x, int y) const
{
    return x >= 0 && x < mapWidth && y >= 0 && y < mapHeight;
}
