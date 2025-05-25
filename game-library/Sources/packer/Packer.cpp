//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "packer/Packer.h"

void EncryptData(char* data, size_t size, char key)
{
    for (size_t i = 0; i < size; i++)
    {
        char& byte = *(data + i);
        byte ^= key;
    }
}

void pak::ListFiles(const std::string& directory, std::vector<std::string>& assets)
{
    std::string searchPath = directory + "\\*.*";
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::string tErrorStr = std::string("Error: Cannot open directory ") + directory;
        BX_LOG(ELogLevel::Error, tErrorStr);
        return;
    }

    do
    {
        std::string fileName = findData.cFileName;
        if (fileName == "." || fileName == "..")
        {
            continue;
        }

        std::string fullPath = directory + "\\" + fileName;
        if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            // If it's a directory, recurse
            ListFiles(fullPath, assets);
        }
        else
        {
            assets.push_back(fullPath);
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
}

void pak::CreatePackFile(const std::vector<std::string>& assetFiles, const std::string& pakFilename)
{
    std::ofstream pakFile(pakFilename, std::ios::binary);
    if (!pakFile)
    {
        std::string tErrorStr = std::string("Failed to create .pak file ") + pakFilename;
        BX_LOG(ELogLevel::Error, tErrorStr);
        return;
    }

    std::vector<FPackEntry> entries;

    // the file begin with the size of the header, set the current offset pass that number:
    uint32_t currentOffset = sizeof(uint32_t);
    pakFile.seekp(sizeof(uint32_t), std::ios::beg);
    for (const auto& filename : assetFiles)
    {
        std::ifstream assetFile(filename, std::ios::binary | std::ios::ate);
        if (!assetFile)
        {
            std::string tErrorStr = std::string("Failed to open asset: ") + filename;
            BX_LOG(ELogLevel::Error, tErrorStr);
            continue;
        }

        FPackEntry entry = {};
        std::string path = std::regex_replace(filename, std::regex(R"(\.\./assets\\)"), "");
        path = std::regex_replace(path, std::regex(R"(\\)"), "/");

        strncpy_s(entry.filename, sizeof(entry.filename), path.c_str(), _TRUNCATE);
        entry.offset = currentOffset;
        entry.size = static_cast<unsigned int>(assetFile.tellg());

        assetFile.seekg(0, std::ios::beg);
        std::vector<char> buffer(entry.size);
        assetFile.read(buffer.data(), entry.size);
        assetFile.close();

        EncryptData(buffer.data(), buffer.size(), 0x5A);
        pakFile.write(buffer.data(), entry.size);
        currentOffset += entry.size;
        entries.push_back(entry);
    }

    auto headerSize = static_cast<uint32_t>(entries.size() * sizeof(FPackEntry));
    char* tHeaderData = reinterpret_cast<char*>(entries.data());
    EncryptData(tHeaderData, headerSize, 0x5A);

    pakFile.write(tHeaderData, headerSize);
    pakFile.seekp(0, std::ios::beg);
    pakFile.write(reinterpret_cast<char*>(&headerSize), sizeof(uint32_t));
    pakFile.close();
}

void pak::ReadPackHeader(const std::string& pakFilename)
{
    std::ifstream pakFile(pakFilename, std::ios::binary);
    if (!pakFile)
    {
        std::string tErrorStr = std::string("Failed to open .pak file ") + pakFilename;
        BX_LOG(ELogLevel::Error, tErrorStr);
        return;
    }

    uint32_t headerSize = 0;
    pakFile.read(reinterpret_cast<char*>(&headerSize), sizeof(uint32_t));

    std::vector<FPackEntry> entries(headerSize / sizeof(FPackEntry));
    pakFile.seekg(-static_cast<int>(headerSize), std::ios::end);

    char* tHeaderData = reinterpret_cast<char*>(entries.data());
    pakFile.read(tHeaderData, headerSize);
    EncryptData(tHeaderData, headerSize, 0x5A);

    for (const auto& entry : entries)
    {
        std::string tEntry = std::string(entry.filename);
        BX_LOG(ELogLevel::Log, tEntry);
    }

    pakFile.close();
}

std::vector<char> pak::FindAsset(const std::string& assetName, const std::string& pakFilename)
{
    std::ifstream pakFile(pakFilename, std::ios::binary);
    if (!pakFile)
    {
        BX_LOG(ELogLevel::Error, "Failed to open .pak file!");
        return {};
    }

    uint32_t headerSize = 0;
    pakFile.read(reinterpret_cast<char*>(&headerSize), sizeof(uint32_t));

    std::vector<FPackEntry> entries(headerSize / sizeof(FPackEntry));
    pakFile.seekg(-static_cast<int>(headerSize), std::ios::end);

    char* tHeaderData = reinterpret_cast<char*>(entries.data());
    pakFile.read(tHeaderData, headerSize);
    EncryptData(tHeaderData, headerSize, 0x5A);

    for (const auto& entry : entries)
    {
        if (strcmp(entry.filename, assetName.c_str()) == 0)
        {
            pakFile.seekg(entry.offset, std::ios::beg);
            std::vector<char> buffer(entry.size);
            pakFile.read(buffer.data(), entry.size);
            EncryptData(buffer.data(), buffer.size(), 0x5A);
            return buffer;
        }
    }

    std::string tErrorStr = assetName + " not found in " + pakFilename + "\n";
    OutputDebugString(tErrorStr.c_str());
    pakFile.close();
    return {};
}
