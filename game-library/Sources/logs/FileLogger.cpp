//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "logs/FileLogger.h"

FileLogger::FileLogger() :
    FileLogger("logs.txt")
{
}

FileLogger::FileLogger(const std::string& filename) :
    m_LogFile(filename)
{
}

FileLogger::~FileLogger()
{
    if (m_LogFile.is_open())
    {
        try
        {
            m_LogFile.close();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error closing log file: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown error occurred while closing log file." << std::endl;
        }
    }
}

void FileLogger::WriteLog(const std::string& message)
{
    if (m_LogFile.is_open())
    {
        m_LogFile << message << std::endl;
    }
}
