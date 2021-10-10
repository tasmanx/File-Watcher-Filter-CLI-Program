#include <iostream>
#include <string>
#include <thread>
#include <chrono>

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
    std::thread t = std::thread(&FileWatcher::startFileWatcher, &fileWatcher, hotFolderPath, backupFolderPath);

    // TODO: add while loop with file filter menu

    t.join();
}