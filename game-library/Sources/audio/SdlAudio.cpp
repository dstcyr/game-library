//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "audio/SdlAudio.h"
#include <SDL_mixer.h>

#if defined(USE_VLD)
#include <vld.h>
#endif

bool SdlAudio::Initialize()
{
#if defined(USE_VLD)
    VLDDisable();
#endif

    std::string sdlVersion = std::to_string(SDL_MIXER_MAJOR_VERSION) + "." + std::to_string(SDL_MIXER_MINOR_VERSION) + "." + std::to_string(SDL_MIXER_PATCHLEVEL);
    BX_LOG(ELogLevel::Log, "SDL_mixer " + sdlVersion);

    bool bOK = true;
    m_NumChannel = 4;
    if (Mix_OpenAudio(48000, AUDIO_S16SYS, m_NumChannel, 4096) != 0)
    {
        const char* errorMessage = Mix_GetError();
        const std::string errorString(errorMessage);
        BX_LOG(ELogLevel::Error, "Error with SDL audio: " + errorString);
        bOK = false;
    }

#if defined(USE_VLD)
    VLDRestore();
#endif

    return bOK;
}

void SdlAudio::Shutdown()
{
    ClearCache();
    Mix_CloseAudio();
    Mix_Quit();
}

size_t SdlAudio::LoadAudio(const std::string& filename)
{
    const size_t soundId = std::hash<std::string>()(filename);
    if (m_SoundDataMap.count(soundId) > 0)
    {
        return soundId;
    }

    IResources& tResources = Game::Get().Resources();

    std::vector<char> rawData = tResources.LoadData(filename);
    if (!rawData.empty())
    {
        SDL_RWops* rWops = SDL_RWFromMem(const_cast<char*>(rawData.data()), static_cast<int>(rawData.size()));
        if (rWops == nullptr)
        {
            std::string sdlError = SDL_GetError();
            BX_LOG(ELogLevel::Error, "SDL_RWFromMem failed: " + sdlError);
            SDL_RWclose(rWops);
            rWops = nullptr;

            return 0;
        }

        Mix_Chunk* sound = Mix_LoadWAV_RW(rWops, 0);
        SDL_RWclose(rWops);
        rWops = nullptr;

        if (sound != nullptr)
        {
            m_SoundDataMap.emplace(soundId, sound);
            return soundId;
        }
    }

    const char* errorMessage = Mix_GetError();
    BX_LOG(ELogLevel::Error, "Cannot load sound: " + filename);
    BX_LOG(ELogLevel::Error, errorMessage);
    return 0;
}

int SdlAudio::PlayAudio(const size_t id, const int loop)
{
    int channel = FindAvailableChannel();
    auto* ptr = static_cast<Mix_Chunk*>(m_SoundDataMap[id]);
    int usedChannel = Mix_PlayChannel(channel, ptr, loop);

    BX_CHECKS(channel == usedChannel, "Not using the specified channel");
    return usedChannel;
}

int SdlAudio::PlaySFX(size_t id)
{
    return PlayAudio(id, 0);
}

void SdlAudio::PlayMusic(size_t id)
{
    auto* ptr = static_cast<Mix_Chunk*>(m_SoundDataMap[id]);
    int channel = Mix_PlayChannel(m_MusicChannel, ptr, -1);
}

void SdlAudio::StopSound(int channel)
{
    BX_CHECKS(channel != 0, "Channel 0 is reserved for music");

    Mix_HaltChannel(channel);
}

void SdlAudio::StopMusic()
{
    Mix_HaltChannel(m_MusicChannel);
}

void SdlAudio::StopAllSounds()
{
    Mix_HaltChannel(-1);
}

bool SdlAudio::IsPlaying(int channel)
{
    BX_CHECKS(channel != 0, "Channel 0 is reserved for music");

    int result = Mix_Playing(channel);
    return result == 1;
}

bool SdlAudio::IsMusicPlaying()
{
    int result = Mix_Playing(m_MusicChannel);
    return result == 1;
}

void SdlAudio::SetVolume(size_t soundId, int volume)
{
    auto* ptr = static_cast<Mix_Chunk*>(m_SoundDataMap[soundId]);
    Mix_VolumeChunk(ptr, volume);
}

void SdlAudio::ClearCache()
{
    for (auto& pair : m_SoundDataMap)
    {
        auto* ptr = static_cast<Mix_Chunk*>(pair.second);
        Mix_FreeChunk(ptr);
        pair.second = nullptr;
    }

    m_SoundDataMap.clear();
}

int SdlAudio::FindAvailableChannel() const
{
    for (int i = 1; i < m_NumChannel; i++)
    {
        if (Mix_Playing(i) == 0)
        {
            return i;
        }
    }

    return 1;
}
