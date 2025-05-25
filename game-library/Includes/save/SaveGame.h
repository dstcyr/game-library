//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SAVE_SAVEGAME_H
#define SAVE_SAVEGAME_H

#include "ISave.h"

class SaveGame : public ISave
{
public:
    bool Save(const std::string& filename) override;
    bool Load(const std::string& filename) override;
    bool Exists(const std::string& filename) override;

private:
    int32_t m_CurrentSaveVersion = 6;
};

#endif
