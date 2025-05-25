//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_ENTITYGRID_H
#define MAPS_ENTITYGRID_H

struct FMapTransform;

struct FEntityGrid
{
    int gridWidth = 0;
    int gridHeight = 0;
    std::vector<std::vector<int>> grid;

    void Draw(const FMapTransform& transform);
    void Reset(int value);
    void Clear();
    void SetSize(int width, int height, int value);
    void Update(int fromX, int fromY, int toX, int toY);
    void Clear(int x, int y);
    bool IsOccupied(int x, int y);
    bool IsValidLocation(int x, int y) const;
};

#endif
