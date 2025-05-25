//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCREENS_SCREENSTATE_H
#define SCREENS_SCREENSTATE_H

#include <string>
#include "utils/IState.h"
#include "scenes/StateInfo.h"

class BufferedFile;

class ScreenState : public IState
{
public:
    void Enter() override {}
    void Exit() override {}
    void Update(float dt) override {}
    bool ProcessInput(float dt) override { return true; }
    void Draw() override {}

    virtual void Pause() {}
    virtual void Resume() {}
    virtual void Destroy() {}

    virtual FStateInfo GetStateInfo() { return {}; }
    virtual std::string GetTileType(int x, int y) { return ""; }

    virtual void Save(BufferedFile* saveFile) {}
    virtual void Load(BufferedFile* saveFile) {}
};

#endif
