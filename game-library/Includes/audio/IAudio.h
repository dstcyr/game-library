//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef AUDIO_IAUDIO_H
#define AUDIO_IAUDIO_H

#include <string>

class IAudio
{
public:
    virtual ~IAudio() = default;
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual size_t LoadAudio(const std::string& filename) = 0;
    virtual int PlayAudio(size_t id, int loop) = 0;
    virtual int PlaySFX(size_t id) = 0;
    virtual void PlayMusic(size_t id) = 0;
    virtual void StopSound(int channel) = 0;
    virtual void StopMusic() = 0;
    virtual void StopAllSounds() = 0;
    virtual bool IsPlaying(int channel) = 0;
    virtual bool IsMusicPlaying() = 0;
    virtual void SetVolume(size_t soundId, int volume) = 0;
    virtual void ClearCache() = 0;
};

#endif
