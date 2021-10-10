#include <iostream>
#include <string>

#include "CLI.h"
#include "FileWatcher.h"
#include "Logger.h"

using std::string;

int main() 
{
    std::cout << "Welcome to File-Watcher-Filter-CLI-Program" << std::endl;
    string hotFolderPath, backupFolderPath;
    CLI::GetHotAndBackupFolderPaths(hotFolderPath, backupFolderPath);

    Logger logger("log.txt");
    FileWatcher fileWatcher(logger);
    fileWatcher.startFileWatcher(hotFolderPath, backupFolderPath);
}