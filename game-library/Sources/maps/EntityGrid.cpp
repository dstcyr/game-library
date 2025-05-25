//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/EntityGrid.h"
#include "maps/MapTransform.h"

void FEntityGrid::Draw(const FMapTransform& transform)
{
#if defined(SHOW_ENTITY_GRID)
    IGraphics& tGraphics = Game::Get().Graphics();
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            if (grid[y][x] != 0)
            {
                float worldX = 0.0F;
                float worldY = 0.0F;
                transform.ToWorld(x, y, &worldX, &worldY);
                tGraphics.FillRect(
                    worldX,
                    worldY,
                    static_cast<float>(transform.tileWidth),
                    static_cast<float>(transform.tileHeight),
                    0, 0, 255, 80
                );
            }
        }
    }
#endif
}

void FEntityGrid::Reset(int value)
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            grid[y][x] = value;
        }
    }
}

void FEntityGrid::Clear()
{
    for (auto it = grid.begin(); it != grid.end(); it++)
    {
        it->clear();
    }

    grid.clear();
}

void FEntityGrid::SetSize(int width, int height, int value)
{
    gridWidth = width;
    gridHeight = height;
    grid.resize(height, std::vector<int>(width, value));
}

void FEntityGrid::Update(int fromX, int fromY, int toX, int toY)
{
    Clear(fromX, fromY);

    if (IsValidLocation(toX, toY))
    {
        grid[toY][toX] = 1;
    }
}

void FEntityGrid::Clear(int x, int y)
{
    if (IsValidLocation(x, y))
    {
        grid[y][x] = 0;
    }
}

bool FEntityGrid::IsOccupied(int x, int y)
{
    if (IsValidLocation(x, y))
    {
        return grid[y][x] != 0;
    }

    return false;
}

bool FEntityGrid::IsValidLocation(int x, int y) const
{
    return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}
