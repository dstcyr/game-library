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

#ifndef SCREENS_STORYBOARD_H
#define SCREENS_STORYBOARD_H

#include "screens/ScreenState.h"
#include "data/Stack.h"
#include "storyboard/IStoryboardEvent.h"
#include "utils/StateStack.h"
#include <vector>
#include <functional>
#include <map>

class Tilemap;
class StoryState;

class Storyboard : public ScreenState
{
public:
    void Enter() override;
    void Update(float deltaTime) override;
    bool ProcessInput(float deltaTime) override;
    void Draw() override;
    void Exit() override;

    StoryState* Find(const std::string& id);
    void RemoveState(const std::string& id);
    void AddSound(const std::string& filename, int channel);
    void StopSound(const std::string& filename);

    void AddMap(Tilemap* map);
    void RemoveMap(Tilemap* map);
    Tilemap* GetMap(const std::string& mapName);

private:
    TArray<IStoryboardEvent> m_Events;
    // StateStack m_SubStack;

    TArray<StoryState> m_StoryStack;


    size_t m_DefaultFont = 0;
    std::vector<std::function<IStoryboardEvent* (Storyboard*)>> m_StoryEvents;
    std::map<std::string, int> m_AudioChannels;


    TArray<Character> m_Characters;
    TArray<Tilemap> m_Maps;
};

#endif
