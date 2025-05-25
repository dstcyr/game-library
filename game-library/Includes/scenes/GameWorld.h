//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_GAMEWORLD_H
#define SCENES_GAMEWORLD_H

#include "IWorld.h"
#include "maps/Tileset.h"
#include "properties/PropertyCollection.h"
#include "ScreenStateMachine.h"

class ObjectLayer;
class Layer;
class Camera;
class Character;
class Trigger;

namespace tinyxml2 
{ 
    class XMLNode;
    class XMLElement;
}

class GameWorld : public IWorld
{
public:
    void Save(BufferedFile* saveFile) override;
    void Load(BufferedFile* saveFile) override;
    PropertyCollection& GetPersistence() override;
    bool ProcessInput(float deltaTime) override;
    void Update(float deltaTime) override;
    void Draw() override;
    void Shutdown() override;
    ControllerState* CreateController(const std::string& name, const std::string& next) override;
    void StartNewGame() override;
    Character* GetHero() override;
    Camera* GetCamera() override;
    void FadeToState(const std::string& state, bool startWithBlackScreen) override;
    void ChangeState(const std::string& state) override;
    void PushState(const std::string& state) override;
    void PopState() override;
    void ReplaceState(const std::string& state) override;
    void FadeIn() override;
    void FadeOut(const std::function<void()>& callback) override;
    FStateInfo GetStateInfo() override;
    std::string GetTileType(int x, int y) override;

    void ClearStates() override;
    void RegisterState(const std::string& name, ScreenState* state) override;
    void RegisterControllerFactory(const std::string& name, TControllerFactory factory) override;

private:

    std::map<std::string, TControllerFactory> m_ControllerFactories;
    PropertyCollection m_Persistence;
    ScreenStateMachine m_StateMachine;
    Character* m_Hero = nullptr;
    Camera* m_Camera = nullptr;
};

#endif
