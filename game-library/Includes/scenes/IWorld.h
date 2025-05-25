//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_IWORLD_H
#define SCENES_IWORLD_H

#include "StateInfo.h"
#include <string>
#include <functional>
#include "screens/ScreenState.h"

class Entity;
class MapPropertyCollection;
class ControllerState;
class TileLayer;
class Character;
class Trigger;
class BufferedFile;
class PropertyCollection;
class Camera;

using TControllerFactory = std::function<ControllerState* (const std::string&)>;

class IWorld
{
public:
    virtual ~IWorld() = default;
    virtual void Save(BufferedFile* saveFile) = 0;
    virtual void Load(BufferedFile* saveFile) = 0;
    virtual PropertyCollection& GetPersistence() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual bool ProcessInput(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void Shutdown() = 0;
    virtual ControllerState* CreateController(const std::string& name, const std::string& next) = 0;
    virtual void StartNewGame() = 0;
    virtual Character* GetHero() = 0;
    virtual Camera* GetCamera() = 0;
    virtual void ChangeState(const std::string& state) = 0;
    virtual void FadeToState(const std::string& state, bool startWithBlackScreen) = 0;
    virtual void PushState(const std::string& state) = 0;
    virtual void PopState() = 0;
    virtual void ReplaceState(const std::string& state) = 0;
    virtual void FadeIn() = 0;
    virtual void FadeOut(const std::function<void()>& callback) = 0;

    virtual void ClearStates() = 0;
    virtual void RegisterState(const std::string& name, ScreenState* state) = 0;
    virtual void RegisterControllerFactory(const std::string& name, TControllerFactory factory) = 0;

    virtual FStateInfo GetStateInfo() = 0;
    virtual std::string GetTileType(int x, int y) = 0;
};

#endif
