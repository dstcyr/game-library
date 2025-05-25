//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef AUDIO_SDLAUDIO_H
#define AUDIO_SDLAUDIO_H

#include "IAudio.h"
#include <string>
#include <map>

class SdlAudio final : public IAudio
{
public:
    bool Initialize() override;
    void Shutdown() override;

    size_t LoadAudio(const std::string& filename) override;
    int PlayAudio(size_t id, int loop) override;
    int PlaySFX(size_t id) override;
    void PlayMusic(size_t id) override;
    void StopSound(int channel) override;
    void StopMusic() override;
    void StopAllSounds() override;
    bool IsPlaying(int channel) override;
    bool IsMusicPlaying() override;
    void SetVolume(size_t soundId, int volume) override;
    void ClearCache() override;

private:
    int FindAvailableChannel() const;
    std::map<size_t, void*> m_SoundDataMap;
    int m_MusicChannel = 0;
    int m_NumChannel = 0;
};

#endif
