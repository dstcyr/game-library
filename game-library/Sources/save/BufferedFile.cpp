//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "save/BufferedFile.h"

bool BufferedFile::LoadFromDisk(const std::string& filename)
{
    m_Pos = 0;
    FILE* tFile = nullptr;
    errno_t tFileResult = fopen_s(&tFile, filename.c_str(), "rb");
    if (tFileResult != 0)
    {
        BX_LOG(ELogLevel::Error, "Cannot open file " + filename);
        return false;
    }

    fseek(tFile, 0, SEEK_END);
    m_Size = static_cast<int>(ftell(tFile));
    fseek(tFile, 0, SEEK_SET);

    void* buffer = malloc(m_Size * sizeof(unsigned char));
    memset(buffer, 0, m_Size * sizeof(unsigned char));
    m_FileBuffer = static_cast<unsigned char*>(buffer);
    m_BufferSize = m_Size;

    fread(m_FileBuffer, sizeof(unsigned char), m_Size, tFile);
    fclose(tFile);
    return true;
}

int BufferedFile::PeekVersion(const std::string& filename)
{
    FILE* tFile = nullptr;
    errno_t tFileResult = fopen_s(&tFile, filename.c_str(), "rb");
    if (tFileResult != 0)
    {
        return -1;
    }

    int version = 0;
    if (fread(&version, sizeof(int), 1, tFile) != 1) 
    {
        fclose(tFile);
        return -1;
    }

    fclose(tFile);
    return version;
}

void BufferedFile::CreateBuffer(int bufferSize)
{
    m_Pos = 0;
    m_Size = 0;
    m_BufferSize = bufferSize;

    void* buffer = malloc(m_BufferSize * sizeof(unsigned char));
    memset(buffer, 0, m_BufferSize * sizeof(unsigned char));
    m_FileBuffer = static_cast<unsigned char*>(buffer);
}

bool BufferedFile::WriteToDisk(const std::string& filename)
{
    FILE* tFile = nullptr;
    errno_t tFileResult = fopen_s(&tFile, filename.c_str(), "wb");
    if (tFileResult != 0)
    {
        BX_LOG(ELogLevel::Error, "Cannot open file " + filename);
        return false;
    }

    fwrite(m_FileBuffer, 1, m_Size, tFile);
    fclose(tFile);
    return true;
}

void BufferedFile::Seek(int position)
{
    m_Pos = position;
}

int BufferedFile::GetSize() const
{
    return m_Size;
}

void BufferedFile::WriteInt8(int8_t value)
{
    WriteToBuffer(&value, sizeof(int8_t));
}

void BufferedFile::WriteBool(bool value)
{
    WriteInt8(value ? 1 : 0);
}

void BufferedFile::WriteInt16(int16_t value)
{
    WriteToBuffer(&value, sizeof(int16_t));
}

void BufferedFile::WriteInt32(int32_t value)
{
    WriteToBuffer(&value, sizeof(int32_t));
}

void BufferedFile::WriteInt64(int64_t value)
{
    WriteToBuffer(&value, sizeof(int64_t));
}

void BufferedFile::WriteUInt8(uint8_t value)
{
    WriteToBuffer(&value, sizeof(uint8_t));
}

void BufferedFile::WriteUInt16(uint16_t value)
{
    WriteToBuffer(&value, sizeof(uint16_t));
}

void BufferedFile::WriteUInt32(uint32_t value)
{
    WriteToBuffer(&value, sizeof(uint32_t));
}

void BufferedFile::WriteUInt64(uint64_t value)
{
    WriteToBuffer(&value, sizeof(uint64_t));
}

void BufferedFile::WriteFloat(float_t value)
{
    WriteToBuffer(&value, sizeof(float_t));
}

void BufferedFile::WriteDouble(double_t value)
{
    WriteToBuffer(&value, sizeof(double_t));
}

void BufferedFile::WriteString(const std::string& value)
{
    int strLength = static_cast<int>(value.size());
    WriteInt32(strLength);

    memcpy(m_FileBuffer + m_Pos, value.c_str(), value.size());
    m_Pos += strLength;
    m_Size += strLength;
}

void BufferedFile::ReadInt8(int8_t* value)
{
    ReadFromBuffer(value, sizeof(int8_t));
}

void BufferedFile::ReadBool(bool* value)
{
    int8_t valueInt = 0;
    ReadInt8(&valueInt);
    *value = valueInt != 0;
}

void BufferedFile::ReadInt16(int16_t* value)
{
    ReadFromBuffer(value, sizeof(int16_t));
}

void BufferedFile::ReadInt32(int32_t* value)
{
    ReadFromBuffer(value, sizeof(int32_t));
}

void BufferedFile::ReadInt64(int64_t* value)
{
    ReadFromBuffer(value, sizeof(int64_t));
}

void BufferedFile::ReadUInt8(uint8_t* value)
{
    ReadFromBuffer(value, sizeof(uint8_t));
}

void BufferedFile::ReadUInt16(uint16_t* value)
{
    ReadFromBuffer(value, sizeof(uint16_t));
}

void BufferedFile::ReadUInt32(uint32_t* value)
{
    ReadFromBuffer(value, sizeof(uint32_t));
}

void BufferedFile::ReadUInt64(uint64_t* value)
{
    ReadFromBuffer(value, sizeof(uint64_t));
}

void BufferedFile::ReadFloat(float_t* value)
{
    ReadFromBuffer(value, sizeof(float_t));
}

void BufferedFile::ReadDouble(double_t* value)
{
    ReadFromBuffer(value, sizeof(double_t));
}

void BufferedFile::ReadString(std::string& value)
{
    int strLength = 0;
    ReadInt32(&strLength);

    void* strBuffer = malloc(strLength);
    memset(strBuffer, 0, strLength);
    memcpy(strBuffer, m_FileBuffer + m_Pos, strLength);

    value = std::string(static_cast<const char*>(strBuffer), strLength);
    free(strBuffer);

    m_Pos += strLength;
}

void BufferedFile::ReadFromBuffer(void* data, int size)
{
    if ((m_Pos + size) > m_Size)
    {
        size = m_Size - m_Pos;
    }

    memcpy(data, m_FileBuffer + m_Pos, size);
    m_Pos += size;
}

void BufferedFile::WriteToBuffer(void* data, int size)
{
    memcpy(m_FileBuffer + m_Pos, data, size);
    m_Pos += size;
    m_Size += size;
}

void BufferedFile::CloseBuffer()
{
    free(m_FileBuffer);
    m_FileBuffer = nullptr;
    m_Pos = 0;
    m_Size = 0;
    m_BufferSize = 0;
}
