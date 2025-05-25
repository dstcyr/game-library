//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef PACKER_PACKER_H
#define PACKER_PACKER_H

#ifdef _MSC_VER

namespace pak
{
    struct FPackEntry
    {
        char filename[100];         //> Stores the asset name
        unsigned int offset;        //> Offset from the start of file
        unsigned int size;          //> Size of the asset in bytes
    };

    void ListFiles(const std::string& directory, std::vector<std::string>& assets);
    void CreatePackFile(const std::vector<std::string>& assetFiles, const std::string& pakFilename);
    void ReadPackHeader(const std::string& pakFilename);
    std::vector<char> FindAsset(const std::string& assetName, const std::string& pakFilename);
}

#endif
#endif
