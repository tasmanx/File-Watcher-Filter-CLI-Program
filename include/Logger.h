#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

class Logger 
{
public:
    Logger(std::string logFilename);

    static const std::string Created;
    static const std::string BackedUp;
    static const std::string Modified;
    static const std::string Removed;
    
    std::string getCurrentDateTimeStr();
    void writeToLogFile(std::string filename, std::string status);

private:
    std::string m_logFilename;
};

#endif // LOGGER_H