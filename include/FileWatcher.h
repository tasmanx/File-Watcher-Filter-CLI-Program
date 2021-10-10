#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <string>

class FileWatcher
{
public:
    FileWatcher();
    
    void startFileWatcher(const std::string hotFolderPath, const std::string backupFolderPath);

private:
    void createFolders(const std::string hotFolderPath, const std::string backupFolderPath);
    
};

#endif // FILEWATCHER_H