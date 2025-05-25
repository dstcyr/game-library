//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_STATEMACHINE_H
#define SCENES_STATEMACHINE_H

#include "graphics/Fade.h"
#include "StateInfo.h"
#include <string>
#include <map>
#include "data/Stack.h"

class ScreenState;
class BufferedFile;
class IStackCommand;

class ScreenStateMachine
{
public:
    void RegisterState(const std::string& name, ScreenState* state);
    bool ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Draw();
    void PostDraw();
    void Save(BufferedFile* saveFile);
    void SaveState(BufferedFile* saveFile);
    void Load(BufferedFile* saveFile);
    void LoadState(BufferedFile* saveFile);
    void Push(const std::string& name);
    void Pop();
    void Replace(const std::string& name);
    void Change(const std::string& name);
    void FadeTo(const std::string& name, bool startWithBlackScreen);
    void Clear();
    void FadeIn();
    void FadeOut(const std::function<void()>& callback);

    FStateInfo GetStateInfo();
    std::string GetTileType(int x, int y);

private:
    friend class PushCommand;
    friend class PopCommand;
    friend class ChangeCommand;
    friend class ReplaceCommand;
    friend class FadeCommand;

    void InternalPushState(ScreenState* state);
    void InternalPopState();
    void InternalChange(ScreenState* state);
    void InternalReplaceTop(ScreenState* state);
    void InternalFadeToState(ScreenState* state, bool startWithBlackScreen);

    void ClearCommands();
    void ExecuteCommands();
    std::string FindNameOfInstance(ScreenState* inst);

    Fade m_Fade;
    std::map<std::string, ScreenState*> m_StateDatabase;
    std::map<std::string, ScreenState*> m_SaveBlacklist;
    TArray<ScreenState> m_RuntimeStack;
    TArray<IStackCommand> m_StateCommands;
};

#endif
