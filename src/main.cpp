#include <iostream>
#include <string>

#include "CLI.h"
#include "FileWatcher.h"

using std::string;

int main() 
{
    std::cout << "Welcome to File-Watcher-Filter-CLI-Program" << std::endl;
    string hotFolderPath, backupFolderPath;
    CLI::GetHotAndBackupFolderPaths(hotFolderPath, backupFolderPath);

    FileWatcher fileWatcher;
    fileWatcher.startFileWatcher(hotFolderPath, backupFolderPath);
}