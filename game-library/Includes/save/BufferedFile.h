//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SAVE_BUFFEREDFILE_H
#define SAVE_BUFFEREDFILE_H

class BufferedFile final
{
public:
    bool LoadFromDisk(const std::string& filename);
    static int PeekVersion(const std::string& filename);
    void CreateBuffer(int bufferSize);
    bool WriteToDisk(const std::string& filename);
    void CloseBuffer();

    void Seek(int position);
    int GetSize() const;

    void WriteInt8(int8_t value);
    void WriteBool(bool value);
    void WriteInt16(int16_t value);
    void WriteInt32(int32_t value);
    void WriteInt64(int64_t value);
    void WriteUInt8(uint8_t value);
    void WriteUInt16(uint16_t value);
    void WriteUInt32(uint32_t value);
    void WriteUInt64(uint64_t value);
    void WriteFloat(float_t value);
    void WriteDouble(double_t value);
    void WriteString(const std::string& value);
    void WriteToBuffer(void* data, int size);

    void ReadInt8(int8_t* value);
    void ReadBool(bool* value);
    void ReadInt16(int16_t* value);
    void ReadInt32(int32_t* value);
    void ReadInt64(int64_t* value);
    void ReadUInt8(uint8_t* value);
    void ReadUInt16(uint16_t* value);
    void ReadUInt32(uint32_t* value);
    void ReadUInt64(uint64_t* value);
    void ReadFloat(float_t* value);
    void ReadDouble(double_t* value);
    void ReadString(std::string& value);
    void ReadFromBuffer(void* data, int size);

private:
    unsigned char* m_FileBuffer = nullptr;
    int m_Pos = 0;
    int m_Size = 0;
    int m_BufferSize = 0;
};

#endif
