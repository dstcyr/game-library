//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_ENTITY_H
#define SCENES_ENTITY_H
#include "data/Stack.h"

class BufferedFile;
class Tilemap;

enum class EDirection : unsigned char
{
    e_Left,
    e_Right,
    e_Up,
    e_Down
};

class Entity
{
public:
    Entity(size_t instId, std::string name);
    virtual ~Entity() = default;
    virtual bool ProcessInput(float deltaTime);
    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void Draw(float x, float y);
    virtual void Clear();
    virtual void Interact() {}
    virtual void Save(BufferedFile* saveFile) {}
    virtual void Load(BufferedFile* saveFile) {}
    void SetWorldLocation(float worldX, float worldY);
    void SetLocalLocation(int localX, int localY);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetBounds(float worldX, float worldY, float width, float height);
    void SetSize(float width, float height);
    void Move(float dx, float dy);
    void GetWorldLocation(float* worldX, float* worldY) const;
    void GetLocalLocation(int* localX, int* localY) const;
    void GetSize(float* width, float* height) const;
    void GetCenter(float* x, float* y) const;
    float GetX() const { return m_Bounds.x; }
    float GetY() const { return m_Bounds.y; }
    float GetWidth() const { return m_Bounds.width; }
    float GetHeight() const { return m_Bounds.height; }
    Rect<float>& GetBounds() { return m_Bounds; }
    size_t GetInstanceID() const { return m_InstanceId; }
    std::string GetName() const { return m_Name; }
    virtual EDirection GetDirection() const { return EDirection::e_Down; }

    Tilemap* GetParentMap() const { return m_ParentMap; }
    void SetParentMap(Tilemap* map) { m_ParentMap = map; }

    void GetSelectPosition(float* posX, float* posY, float width, float height) const;
    void SetSelectPadding(float paddingY);

    void AddChild(Entity* child);
    void RemoveChild(size_t id);

protected:
    size_t m_InstanceId = 0;
    std::string m_Name;
    Rect<float> m_Bounds;
    int m_MapX = 0;
    int m_MapY = 0;
    Tilemap* m_ParentMap = nullptr;
    float m_PaddingY = 0.0F;
    TArray<Entity> m_Children;
};

#endif
