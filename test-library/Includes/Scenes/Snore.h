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

#ifndef SCENES_SNORE_H
#define SCENES_SNORE_H

#include "scenes/Entity.h"
#include <string>
#include "graphics/SpriteSheet.h"
#include "graphics/Animation.h"

class MapPropertyCollection;
class BufferedFile;

class Snore : public Entity
{
public:
    static Entity* Create(const std::string& name);

    Snore(size_t instId, const std::string& name);
    void Initialize();
    void Draw() override;
    void Draw(float x, float y) override;
    void Update(float dt) override;

private:
    std::string m_UId;
    Animation m_SleepAnimation;
};

#endif
