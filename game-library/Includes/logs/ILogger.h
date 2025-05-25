//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef LOGS_ILOGGER_H
#define LOGS_ILOGGER_H

#if defined(SHOW_DEBUG_INFO)
#define USE_LOG_SOURCE
#define LOG_SOURCE_PARAMS , const char* filename, int line
#define LOG_SOURCE , __FILE__, __LINE__
#else
#define LOG_SOURCE_PARAMS 
#define LOG_SOURCE 
#endif

enum class ELogLevel : unsigned char
{
    Log,
    Warning,
    Error
};

class ILogger
{
public:
    virtual ~ILogger() = default;
    void Log(ELogLevel level, const std::string& message LOG_SOURCE_PARAMS);
    void Add(const std::string& message);
    void SetLevel(ELogLevel logLevel);

protected:
    ELogLevel m_Level = ELogLevel::Log;

    virtual void WriteLog(const std::string& message) = 0;
};

#endif
