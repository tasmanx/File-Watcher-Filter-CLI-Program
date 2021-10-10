#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include "Logger.h"
#include <string>

class FileWatcher
{
public:
    FileWatcher(Logger &logger);
    
    void startFileWatcher(const std::string hotFolderPath, const std::string backupFolderPath);

private:
    void createFolders(const std::string hotFolderPath, const std::string backupFolderPath);
    
    Logger m_logger;
};

#endif // FILEWATCHER_H