//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_CHARACTER_H
#define SCENES_CHARACTER_H

#include "controllers/Controller.h"

class MapPropertyCollection;
class Blackboard;
class BufferedFile;

class Character : public Entity
{
public:
    static Entity* Create(const MapPropertyCollection& definition, Tilemap* map);

    Character(size_t instId, const std::string& name);

    bool Load(const std::string& filename);
    bool ProcessInput(float dt) override;
    void Update(float dt) override;
    void Draw() override;
    void Draw(float x, float y) override;
    void Interact() override;
    void Save(BufferedFile* saveFile) override;
    void Load(BufferedFile* saveFile) override;
    EDirection GetDirection() const override;
    void Clear() override;
    void PlayAnimation(const std::string& clipName, bool bLoop = false, bool bHoldLast = false);
    void PlayAnimationOnce(const std::string& clipName, const std::function<void()>& callback);
    void StopAnimation();
    std::string GetCurrentClipName();
    void SetAnimationFrame(const std::string& clipName);
    bool IsLooping() const;

    Blackboard* GetBlackboard() { return m_Controller.GetBlackboard(); }

    void PauseControls();
    void ResumeControls();
    void SetController(const std::string& controllerName);

    void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    void SetState(const std::string& stateName);

private:
    void LoadClips(tinyxml2::XMLNode* node);
    void LoadControllers(tinyxml2::XMLNode* definitionNode);

    Animation m_AnimatedSprite;
    Controller m_Controller{};
    std::string m_DefaultControllerState;
};

#endif
