//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "maps/Tilemap.h"

Entity::Entity(size_t instId, std::string name) :
   m_Name(std::move(name)), m_InstanceId(instId)
{
}

bool Entity::ProcessInput(float deltaTime)
{
    return true;
}

void Entity::Update(float deltaTime)
{
}

void Entity::Draw()
{
}

void Entity::Draw(float x, float y)
{
}

void Entity::Clear()
{

}

void Entity::SetWorldLocation(float worldX, float worldY)
{
    m_Bounds.x = worldX;
    m_Bounds.y = worldY;
}

void Entity::SetLocalLocation(int localX, int localY)
{
    if (m_ParentMap != nullptr)
    {
        m_ParentMap->GetEntityGrid().Update(m_MapX, m_MapY, localX, localY);
    }

    m_MapX = localX;
    m_MapY = localY;
}

void Entity::SetWidth(float width)
{
    m_Bounds.width = width;
}

void Entity::SetHeight(float height)
{
    m_Bounds.height = height;
}

void Entity::SetBounds(float worldX, float worldY, float width, float height)
{
    m_Bounds.Set(worldX, worldY, width, height);
}

void Entity::SetSize(float width, float height)
{
    m_Bounds.width = width;
    m_Bounds.height = height;
}

void Entity::Move(float dx, float dy)
{
    m_Bounds.x += dx;
    m_Bounds.y += dy;
}

void Entity::GetWorldLocation(float* worldX, float* worldY) const
{
    *worldX = m_Bounds.x;
    *worldY = m_Bounds.y;
}

void Entity::GetLocalLocation(int* localX, int* localY) const
{
    *localX = m_MapX;
    *localY = m_MapY;
}

void Entity::GetSize(float* width, float* height) const
{
    *width = m_Bounds.width;
    *height = m_Bounds.height;
}

void Entity::GetCenter(float* x, float* y) const
{
    *x = m_Bounds.x + m_Bounds.width * 0.5F;
    *y = m_Bounds.y + m_Bounds.height * 0.5F;
}

void Entity::GetSelectPosition(float* posX, float* posY, float width, float height) const
{
    *posX = m_Bounds.x + (m_Bounds.width / 2.0F) - (width / 2.0F);
    *posY = m_Bounds.y - height + m_PaddingY;
}

void Entity::SetSelectPadding(float paddingY)
{
    m_PaddingY = paddingY;
}

void Entity::AddChild(Entity* child)
{
    m_Children.PushBack(child);
}

void Entity::RemoveChild(size_t id)
{
    m_Children.Remove([id](const Entity* entity)
        { 
            return entity->GetInstanceID() == id;
        }
    );
}
