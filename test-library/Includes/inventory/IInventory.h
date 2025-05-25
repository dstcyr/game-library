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

#ifndef INVENTORY_IINVENTORY_H
#define INVENTORY_IINVENTORY_H

#include <cinttypes>

class Entity;
class BufferedFile;

enum class FItems : uint8_t
{
    NONE = 0,
    SMALL_POTION = 1,
    MEDIUM_POTION = 2,
    LARGE_POTION = 3
};

struct FItemEffects
{
    static std::map<FItems, std::function<void(Entity*)>> Effects;
};

struct FItemDefinition
{
    FItems id;
    std::string name;
    std::string description;
    bool consumable;
    bool usable;
    bool equipable;

    FItemDefinition() : id(FItems::NONE), consumable(false), usable(false), equipable(false) {}
    FItemDefinition(FItems inId, std::string inName, std::string inDesc, bool inConsumable, bool inUsable, bool inEquipable) :
        id(inId), name(std::move(inName)), description(std::move(inDesc)), consumable(inConsumable), usable(inUsable), equipable(inEquipable) {
    }

    static FItemDefinition Empty;
};

struct FItemDatabase
{
    static void BuildDatabase();
    static const FItemDefinition& GetItemDefinition(FItems itemID);

private:
    static std::map<FItems, FItemDefinition> ItemDefinitions;
};

struct FInventorySlot
{
    FItems itemID;
    int count;

    FInventorySlot() : itemID(FItems::NONE), count(-1) {}
    FInventorySlot(FItems inID, int inCount) : itemID(inID), count(inCount) {}

    std::string ToString() const
    {
        const FItemDefinition& item = FItemDatabase::GetItemDefinition(itemID);
        return item.name + " x" + std::to_string(count);
    }
};

class IInventory
{
public:
    virtual ~IInventory() = default;
    virtual void Initialize() = 0;
    virtual void Save(BufferedFile* saveFile) = 0;
    virtual void Load(BufferedFile* saveFile) = 0;
    virtual void AddItem(FItems itemID, int count) = 0;
    virtual void Use(int slotIndex, Entity* user) = 0;
    virtual void Print() const = 0;
    virtual std::vector<FInventorySlot> GetItems() = 0;
};

#endif
