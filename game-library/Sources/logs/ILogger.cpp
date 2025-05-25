//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

void ILogger::Log(ELogLevel level, const std::string& message LOG_SOURCE_PARAMS)
{
    if (level < m_Level) { return; }

    std::string sourceStr;

#if defined(USE_LOG_SOURCE)
    sourceStr = "\n\t" + std::string(filename) + " (" + std::to_string(line) + ")";
#endif

    std::time_t now = std::time(nullptr);
    std::tm localTime{};
    localtime_s(&localTime, &now);

    std::ostringstream oss;
    oss << "[" << std::put_time(&localTime, "%Y-%m-%d - %H:%M:%S") << "]";
    std::string logMessage = oss.str();

    switch (level)
    {
    case ELogLevel::Log:
        logMessage += " [log]: ";
        break;
    case ELogLevel::Warning:
        logMessage += " [warning]: ";
        break;
    case ELogLevel::Error:
        logMessage += " [error]: ";
        break;
    }

    WriteLog(logMessage + message + sourceStr);
}

void ILogger::Add(const std::string& message)
{
    WriteLog("\t" + message);
}

void ILogger::SetLevel(ELogLevel logLevel)
{
    m_Level = logLevel;
}
