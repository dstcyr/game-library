//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef LOGS_FILELOGGER_H
#define LOGS_FILELOGGER_H

class FileLogger : public ILogger
{
public:
    FileLogger();
    explicit FileLogger(const std::string& filename);
    ~FileLogger() override;

protected:
    void WriteLog(const std::string& message) override;

private:
    std::ofstream m_LogFile;
};

#endif
