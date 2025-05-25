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

#ifndef SCENES_CHEST_H
#define SCENES_CHEST_H

#include "scenes/Entity.h"
#include <string>
#include "graphics/SpriteSheet.h"

class MapPropertyCollection;
class BufferedFile;

class Chest : public Entity
{
public:
    static Entity* Create(const MapPropertyCollection& definition, Tilemap* map);

    Chest(size_t instId, const std::string& name);
    void Initialize();
    void Load(BufferedFile* saveFile) override;
    void Draw() override;
    void Draw(float x, float y) override;
    void Interact() override;
    void Open();
    bool IsOpen() const { return m_Open; }

private:
    SpriteSheet m_SpriteSheet;
    bool m_Open = false;
    std::string m_UId;
    size_t m_UnlockSFX = 0;
};

#endif
