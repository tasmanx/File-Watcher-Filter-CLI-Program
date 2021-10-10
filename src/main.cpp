#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>

#include "CLI.h"
#include "FileWatcher.h"
#include "Logger.h"

int main() 
{
    std::cout << "Welcome to File-Watcher-Filter-CLI-Program" << std::endl;
    std::string hotFolderPath, backupFolderPath;
    CLI::GetHotAndBackupFolderPaths(hotFolderPath, backupFolderPath);

    std::unique_ptr logger = std::make_unique<Logger>("log.txt"); 
    FileWatcher fileWatcher(logger.get());
    std::thread t = std::thread(&FileWatcher::startFileWatcher, &fileWatcher, hotFolderPath, backupFolderPath);
    std::cout << "File Watcher on hot folder has started!" << std::endl;

    CLI::StartFilesFilter(logger.get());

    t.join();
}