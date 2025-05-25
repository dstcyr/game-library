//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_EXPLORESTATE_H
#define STORYBOARD_EXPLORESTATE_H

#include "StoryState.h"
#include <string>
#include "scenes/Camera.h"
#include "maps/TileMap.h"

class ExploreState : public StoryState
{
public:
    static StoryState* Create(Storyboard* screen, const std::string& id, const std::string& map);

    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    bool ProcessInput(float dt) override;
    void Draw() override;

private:
    ExploreState(Storyboard* screen, const std::string& id, const std::string& map);

    std::string m_MapName;
    Camera* m_Camera = nullptr;
    Tilemap* m_Map = nullptr;
};

#endif
