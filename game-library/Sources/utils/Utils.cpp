//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

size_t Utils::GenerateID(const std::string& name)
{
    BX_CHECKS(!name.empty(), "Name is empty");

    size_t id = std::hash<std::string>()(name);
    return id;
}

size_t Utils::GenerateID(const std::string& name, int num)
{
    BX_CHECKS(!name.empty(), "Name is empty");

    std::string objectHashStr = name + std::to_string(num);
    size_t id = std::hash<std::string>()(objectHashStr);
    return id;
}
