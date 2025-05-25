//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef MAPS_LAYER_H
#define MAPS_LAYER_H

class Tilemap;

class Layer
{
public:
    virtual ~Layer() = default;
    virtual void Draw() = 0;
    virtual void PostDraw() {}
    virtual void Clear() = 0;
    virtual int IndexAtLocation(int x, int y) { return -1; }

    void SetParentMap(Tilemap* map) { m_ParentMap = map; }

    const std::string& GetName() const { return m_LayerName; }

protected:
    std::string m_LayerName;
    Tilemap* m_ParentMap = nullptr;
};

#endif
