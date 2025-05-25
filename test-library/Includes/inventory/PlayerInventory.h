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

#ifndef INVENTORY_PLAYERINVENTORY_H
#define INVENTORY_PLAYERINVENTORY_H

#include "IInventory.h"

class Entity;

class PlayerInventory : public IInventory
{
public:
    static IInventory& Get();

    void Initialize() override;
    void Save(BufferedFile* saveFile) override;
    void Load(BufferedFile* saveFile) override;
    void AddItem(FItems itemID, int count) override;
    void Use(int slotIndex, Entity* user) override;
    void Print() const override;
    virtual std::vector<FInventorySlot> GetItems();

private:
    int FindStackIndex(FItems itemID);

    std::vector<FInventorySlot> m_Slots;
};

#endif
