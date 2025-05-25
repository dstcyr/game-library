//  
//     _ ____  ____   ____   ____            _        
//    (_)  _ \|  _ \ / ___| |  _ \ _ __ ___ | |_ ___  
//    | | |_) | |_) | |  _  | |_) | '__/ _ \| __/ _ \ 
//    | |  _ <|  __/| |_| | |  __/| | | (_) | || (_) |
//   _/ |_| \_\_|    \____| |_|   |_|  \___/ \__\___/ 
//  |__/                                              
//  
//  jRPG Prototype
//  Copyright(C) 2024-2025 David St-Cyr
//  
//  The information in this file is confidential and solely for the attention
//  and use of the author. You are hereby notified that any dissemination,
//  distribution or copy of this content is prohibited without the prior
//  written consent of the author.
//
//  David St-Cyr
//  st-cyrdavid@hotmail.com

#include "Config.h"
#include "inventory/PlayerInventory.h"
#include "save/BufferedFile.h"

FItemDefinition FItemDefinition::Empty;
std::map<FItems, FItemDefinition> FItemDatabase::ItemDefinitions;

void FItemDatabase::BuildDatabase()
{
    ItemDefinitions.clear();

    ItemDefinitions.emplace(FItems::SMALL_POTION, FItemDefinition(FItems::SMALL_POTION, "Small Potion", "Heal a small amount of HP", true, true, false));
    ItemDefinitions.emplace(FItems::MEDIUM_POTION, FItemDefinition(FItems::MEDIUM_POTION, "Medium Potion", "Heal a medium amount of HP", true, true, false));
    ItemDefinitions.emplace(FItems::LARGE_POTION, FItemDefinition(FItems::LARGE_POTION, "Large Potion", "Heal a large amount of HP", true, true, false));
}

const FItemDefinition& FItemDatabase::GetItemDefinition(FItems itemID)
{
    if (ItemDefinitions.count(itemID) > 0)
    {
        return ItemDefinitions[itemID];
    }

    return FItemDefinition::Empty;
}

IInventory& PlayerInventory::Get()
{
    static PlayerInventory inventory;
    return inventory;
}

void PlayerInventory::Initialize()
{
    FItemDatabase::BuildDatabase();
}

void PlayerInventory::Save(BufferedFile* saveFile)
{
    int count = static_cast<int>(m_Slots.size());
    saveFile->WriteInt32(count);

    for (FInventorySlot& slot : m_Slots)
    {
        saveFile->WriteToBuffer(&slot, sizeof(FInventorySlot));
    }
}

void PlayerInventory::Load(BufferedFile* saveFile)
{
    m_Slots.clear();
    int count = 0;
    saveFile->ReadInt32(&count);

    for (int i = 0; i < count; i++)
    {
        FInventorySlot slot;
        saveFile->ReadFromBuffer(&slot, sizeof(FInventorySlot));
        m_Slots.push_back(slot);
    }
}

void PlayerInventory::AddItem(FItems itemID, int count)
{
    int foundIndex = FindStackIndex(itemID);
    if (foundIndex >= 0)
    {
        FInventorySlot& slot = m_Slots[foundIndex];
        slot.count += count;
    }
    else
    {
        m_Slots.emplace_back(itemID, count);
    }
}

void PlayerInventory::Use(int slotIndex, Entity* user)
{
    if (slotIndex < m_Slots.size())
    {
        FInventorySlot& slot = m_Slots[slotIndex];
        const FItemDefinition& itemDefinition = FItemDatabase::GetItemDefinition(slot.itemID);
        if (itemDefinition.usable)
        {
            FItemEffects::Effects[slot.itemID](user);
            if (itemDefinition.consumable)
            {
                slot.count--;
                if (slot.count <= 0)
                {
                    m_Slots.erase(m_Slots.begin() + slotIndex);
                }
            }
        }
    }
}

void PlayerInventory::Print() const
{
    ILogger& tLogger = Game::Get().Logger();
    BX_LOG(ELogLevel::Log, "Player Inventory");
    for (const FInventorySlot& slot : m_Slots)
    {
        tLogger.Add(slot.ToString());
    }
}

std::vector<FInventorySlot> PlayerInventory::GetItems()
{
    return m_Slots;
}

int PlayerInventory::FindStackIndex(FItems itemID)
{
    int len = static_cast<int>(m_Slots.size());
    for (int i = 0; i < len; i++)
    {
        FInventorySlot& slot = m_Slots[i];
        if (slot.itemID == itemID)
        {
            return i;
        }
    }

    return -1;
}

std::map<FItems, std::function<void(Entity*)>> FItemEffects::Effects = {
        { FItems::SMALL_POTION, [](Entity* user)
    {
        BX_LOG(ELogLevel::Log, "Using a small potion");
    }},
        { FItems::MEDIUM_POTION, [](Entity* user)
    {
        BX_LOG(ELogLevel::Log, "Using a medium potion");
    }},
        { FItems::LARGE_POTION, [](Entity* user)
    {
        BX_LOG(ELogLevel::Log, "Using a large potion");
    }}

};
