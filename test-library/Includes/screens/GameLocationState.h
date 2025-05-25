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

#ifndef SCREENS_GAMELOCATIONSTATE_H
#define SCREENS_GAMELOCATIONSTATE_H

#include "screens/ScreenState.h"

class Character;
class Camera;
class Tilemap;

struct FLevelConfig
{
    std::string mapName;
    std::string themeName;
};

class GameLocationState : public ScreenState
{
public:
    GameLocationState() = default;
    explicit GameLocationState(FLevelConfig config);

    void Enter() override;
    bool ProcessInput(float deltaTime) override;
    void Update(float deltaTime) override;
    void Draw() override;
    void Exit() override;
    void Destroy() override;
    void Pause() override;
    void Resume() override;
    FStateInfo GetStateInfo() override;
    std::string GetTileType(int x, int y) override;

    void Save(BufferedFile* saveFile) override;
    void Load(BufferedFile* saveFile) override;

protected:
    void UseMap(const std::string& mapName);
    void UseMusic(const std::string& themeSong);

    FLevelConfig m_LevelConfig;

    size_t m_Font = 0;
    size_t m_Theme = 0;
    int m_AudioChannel = 0;

    Character* m_Hero = nullptr;
    Camera* m_Camera = nullptr;
    Tilemap* m_Map = nullptr;
};

#endif
