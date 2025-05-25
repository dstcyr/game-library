//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "save/SaveGame.h"
#include "save/BufferedFile.h"

bool SaveGame::Save(const std::string& filename)
{
    BufferedFile saveFile;
    saveFile.CreateBuffer(1024);

    saveFile.WriteInt32(m_CurrentSaveVersion);

    IWorld& tWorld = Game::Get().World();
    tWorld.Save(&saveFile);

    saveFile.WriteToDisk(filename);
    saveFile.CloseBuffer();
    return true;
}

bool SaveGame::Load(const std::string& filename)
{
    BufferedFile saveFile;
    saveFile.LoadFromDisk(filename);

    int32_t saveVersion = 0;
    saveFile.ReadInt32(&saveVersion);

    if (saveVersion == m_CurrentSaveVersion)
    {
        IWorld& tWorld = Game::Get().World();
        tWorld.Load(&saveFile);

        saveFile.CloseBuffer();
        return true;
    }

    BX_LOG(ELogLevel::Warning, "Save file is not compatible with this version of the game");
    saveFile.CloseBuffer();
    return false;
}

bool SaveGame::Exists(const std::string& filename)
{
    BufferedFile saveFile;
    int version = BufferedFile::PeekVersion(filename);
    return version == m_CurrentSaveVersion;
}
