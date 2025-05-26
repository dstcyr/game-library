//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef DATA_STACK_H
#define DATA_STACK_H

#include "utils/Checks.h"
#include "maths/MathUtils.h"
#include <algorithm>
#include <vector>

template<typename T>
class TArray
{
public:
    TArray();

    void Reserve(int count);
    void Resize(int size);
    int Count() const;
    bool IsEmpty() const;

    typename std::vector<T*>::iterator Begin() { return m_Data.begin(); }
    typename std::vector<T*>::iterator End() { return m_Data.end(); }

    void PushBack(T* elem);
    void PushFront(T* elem);
    T* PopBack();
    T* PopFront();

    void Sort();
    void Sort(std::function<bool(const T* const, const T* const)> predicate);

    void Clear();

    void Remove(int index);
    void RemoveFirst();
    void RemoveLast();
    void Remove(std::function<bool(const T*)> predicate);
    typename std::vector<T*>::iterator Remove(typename std::vector<T*>::iterator it);

    T* First();
    T* First() const;
    T* Last();
    T* Last() const;
    T* At(int index);
    T* At(int index) const;
    T* Random();
    T* Random() const;
    void Insert(int index, T* elem);
    int Find(std::function<bool(const T*)> predicate) const;
    TArray<T> FindAll(std::function<bool(const T*)> predicate);
    std::vector<T*> ToVector() const;

private:
    std::vector<T*> m_Data;
};

template<typename T>
TArray<T>::TArray()
{
    if (std::is_pointer<T>())
    {
        BX_CHECKS(std::is_pointer<T>(), "Type cannot be a pointer for TArrays");
    }
}

template<typename T>
void TArray<T>::Reserve(int count)
{
    m_Data.reserve(count);
}

template<typename T>
void TArray<T>::Resize(int size)
{
    auto length = static_cast<int>(m_Data.size());
    if (size > length)
    {
        m_Data.resize(size, nullptr);
    }
    else
    {
        m_Data.resize(size);
    }
}

template<typename T>
int TArray<T>::Count() const
{
    auto size = static_cast<int>(m_Data.size());
    return size;
}

template<typename T>
bool TArray<T>::IsEmpty() const
{
    return m_Data.empty();
}


template<typename T>
void TArray<T>::PushFront(T* elem)
{
    m_Data.insert(m_Data.begin(), elem);
}

template<typename T>
void TArray<T>::PushBack(T* elem)
{
    m_Data.push_back(elem);
}

template<typename T>
T* TArray<T>::PopFront()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");

    T* first = m_Data[0];
    Remove(0);
    return first;
}

template<typename T>
T* TArray<T>::PopBack()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");

    auto length = static_cast<int>(m_Data.size());
    T* last = m_Data[length - 1];
    Remove(length - 1);
    return last;
}

template<typename T>
void TArray<T>::Sort(std::function<bool(const T*, const T*)> predicate)
{
    std::sort(m_Data.begin(), m_Data.end(), predicate);
}

template<typename T>
void TArray<T>::Sort()
{
    std::sort(m_Data.begin(), m_Data.end());
}

template<typename T>
void TArray<T>::RemoveLast()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    size_t length = m_Data.size();
    m_Data.erase(Begin() + (length - 1));
}

template<typename T>
void TArray<T>::RemoveFirst()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    m_Data.erase(Begin());
}

template<typename T>
T* TArray<T>::Random()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");

    int len = Count();
    int selection = MathUtils::RandRange(0, len - 1);
    return At(selection);
}

template<typename T>
T* TArray<T>::Random() const
{
    if (IsEmpty())
    {
        return nullptr;
    }

    int len = Count();
    int selection = MathUtils::RandRange(0, len - 1);
    return At(selection);
}

template<typename T>
typename std::vector<T*>::iterator TArray<T>::Remove(typename std::vector<T*>::iterator it)
{
    return m_Data.erase(it);
}

template<typename T>
std::vector<T*> TArray<T>::ToVector() const
{
    std::vector<T*> copies = m_Data;
    return copies;
}

template<typename T>
TArray<T> TArray<T>::FindAll(std::function<bool(const T*)> predicate)
{
    TArray<T> results;
    for (auto it = Begin(); it != End(); it++)
    {
        if (predicate(*it))
        {
            results.PushBack(*it);
        }
    }

    return results;
}

template<typename T>
int TArray<T>::Find(std::function<bool(const T*)> predicate) const
{
    for (size_t i = 0; i < m_Data.size(); i++)
    {
        if (predicate(m_Data[i]))
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

template<typename T>
T* TArray<T>::At(int index) const
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    return *(m_Data.begin() + index);
}

template<typename T>
T* TArray<T>::At(int index)
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    return *(m_Data.begin() + index);
}

template<typename T>
void TArray<T>::Remove(std::function<bool(const T*)> predicate)
{
    auto it = m_Data.begin();
    while (it != m_Data.end())
    {
        if (predicate(*it))
        {
            it = m_Data.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

template<typename T>
void TArray<T>::Remove(int index)
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    m_Data.erase(m_Data.begin() + index);
}

template<typename T>
void TArray<T>::Insert(int index, T* elem)
{
    m_Data.insert(m_Data.begin() + index, elem);
}

template<typename T>
T* TArray<T>::Last()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    size_t length = m_Data.size();
    return m_Data[length - 1];
}

template<typename T>
T* TArray<T>::Last() const
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    size_t length = m_Data.size();
    return m_Data[length - 1];
}

template<typename T>
T* TArray<T>::First()
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    return m_Data[0];
}

template<typename T>
T* TArray<T>::First() const
{
    BX_CHECKS(!m_Data.empty(), "Stack is empty");
    return m_Data[0];
}

template<typename T>
void TArray<T>::Clear()
{
    m_Data.clear();
}

#endif
