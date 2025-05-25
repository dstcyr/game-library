//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GAME_H
#define GAME_H

#include "graphics/Fade.h"
#include "graphics/IGraphics.h"
#include "inputs/IInputs.h"
#include "logs/ILogger.h"
#include "resources/IResources.h"
#include "audio/IAudio.h"
#include "save/ISave.h"
#include "scenes/IWorld.h"
#include "data/Stack.h"

class BufferedFile;
class UINode;

class Game
{
public:
    static Game& Get();
    bool Initialize();
    void Start();
    void QuitGame();

    IGraphics& Graphics() const { return *m_GraphicsInstance; }
    IInputs& Inputs() const { return *m_InputsInstance; }
    ILogger& Logger() const { return *m_LoggerInstance; }
    IResources& Resources() const { return *m_ResourceInstance; }
    IAudio& Audio() const { return *m_AudioInstance; }
    ISave& GetSave() { return *m_SaveInstance; }
    IWorld& World() { return *m_WorldInstance; }

    void PushUINode(UINode* node);
    void FlushUIStack();
    void PopUINode();

private:
    Game() = default;
    void ProcessInput(float dt);
    void Update(float dt);
    void UpdateUI(float dt);
    void Draw();
    void DrawUI();
    void Destroy();

    bool m_IsRunning = false;
    IGraphics* m_GraphicsInstance = nullptr;
    IInputs* m_InputsInstance = nullptr;
    ILogger* m_LoggerInstance = nullptr;
    IResources* m_ResourceInstance = nullptr;
    IAudio* m_AudioInstance = nullptr;
    ISave* m_SaveInstance = nullptr;
    IWorld* m_WorldInstance = nullptr;

    TArray<UINode> m_UIStack;
    TArray<UINode> m_UIStackToDelete;
};

#define BX_LOG(level, message) Game::Get().Logger().Log(level, message LOG_SOURCE)

#endif
