//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SAVE_ISAVE_H
#define SAVE_ISAVE_H

class ISave
{
public:
    virtual ~ISave() = default;
    virtual bool Save(const std::string& filename) = 0;
    virtual bool Load(const std::string& filename) = 0;
    virtual bool Exists(const std::string& filename) = 0;
};

#endif
