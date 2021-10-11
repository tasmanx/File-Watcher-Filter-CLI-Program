#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

class Logger 
{
public:
    Logger(std::string logFilename);
    struct LogData {
        LogData(std::string datetime, std::string filename, std::string status) :
        datetime(datetime), filename(filename), status(status) { }

        std::string datetime;
        std::string filename;
        std::string status;
    };

    static const std::string Created;
    static const std::string BackedUp;
    static const std::string Modified;
    static const std::string Removed;
    
    std::string getCurrentDateTimeStr();
    
    void writeToLogFile(std::string filename, std::string status);
    void readFromLogFile();

    std::vector<LogData> getFilesLogList();

private:
    std::string m_logFilename;
    std::vector<LogData> m_filesLogList;
};

#endif // LOGGER_H