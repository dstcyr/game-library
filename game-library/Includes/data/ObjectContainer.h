//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef DATA_OBJECTCONTAINER_H
#define DATA_OBJECTCONTAINER_H

template<typename T>
class ObjectContainer
{
public:
    void Add(size_t id, const std::string& name, T* object);
    void Remove(size_t id);
    T* Find(size_t id);
    T* Find(const std::string& name);
    bool Exists(size_t id);
    int Count() const;
    void Clear();
    typename std::vector<T*>::iterator Begin() { return m_AllObjects.begin(); }
    typename std::vector<T*>::iterator End() { return m_AllObjects.end(); }

private:
    std::vector<T*> m_AllObjects;
    std::map<size_t, T*> m_ObjectsByID;
    std::map<std::string, T*> m_ObjectsName;
};

template<typename T>
bool ObjectContainer<T>::Exists(size_t id)
{
    return (m_ObjectsByID.count(id) > 0);
}

template<typename T>
void ObjectContainer<T>::Remove(size_t id)
{
    if (m_ObjectsByID.count(id) == 0)
    {
        return;
    }

    T* objToRemove = m_ObjectsByID[id];
    m_ObjectsName.erase(objToRemove->GetName());
    m_ObjectsByID.erase(id);
    for (auto it = m_AllObjects.begin(); it != m_AllObjects.end(); ++it)
    {
        if ((*it) == objToRemove)
        {
            m_AllObjects.erase(it);
            return;
        }
    }
}

template<typename T>
void ObjectContainer<T>::Clear()
{
    for (auto* obj : m_AllObjects)
    {
        if (obj)
        {
            obj->Clear();
            delete obj;
        }
    }

    m_AllObjects.clear();
    m_ObjectsByID.clear();
    m_ObjectsName.clear();
}

template<typename T>
int ObjectContainer<T>::Count() const
{
    return static_cast<int>(m_AllObjects.size());
}

template<typename T>
T* ObjectContainer<T>::Find(const std::string& name)
{
    if (m_ObjectsName.count(name) == 0)
    {
        return nullptr;
    }

    return m_ObjectsName[name];
}

template<typename T>
T* ObjectContainer<T>::Find(size_t id)
{
    if (m_ObjectsByID.count(id) == 0)
    {
        return nullptr;
    }

    return m_ObjectsByID[id];
}

template<typename T>
void ObjectContainer<T>::Add(size_t id, const std::string& name, T* object)
{
    m_AllObjects.emplace_back(object);
    m_ObjectsByID.emplace(id, object);
    m_ObjectsName.emplace(name, object);
}

#endif
