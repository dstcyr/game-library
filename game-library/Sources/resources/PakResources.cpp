//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "resources/PakResources.h"
#include "packer/Packer.h"

PakResources::PakResources(std::string pakFilename) :
    m_PakFilename(std::move(pakFilename))
{
}

std::vector<char> PakResources::LoadData(const std::string& filename)
{
    std::vector<char> buffer = pak::FindAsset(filename, m_PakFilename);
    return buffer;
}
