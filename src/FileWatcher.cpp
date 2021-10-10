#include "FileWatcher.h"
#include "Logger.h"

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>

using std::string;
using std::unordered_map;

FileWatcher::FileWatcher(Logger *logger) : m_logger(logger)
{

}

void FileWatcher::startFileWatcher(const string hotFolderPath, const string backupFolderPath)
{
    // create hot and backup folders if needed
    createFolders(hotFolderPath, backupFolderPath);

    std::chrono::duration<int, std::milli> hotFolderUpdateFrequency = std::chrono::milliseconds(1000);
    unordered_map<string, std::filesystem::file_time_type> filesList;
    string fileDeleteKeyStr = "delete_";

    while (true)
    {
        std::this_thread::sleep_for(hotFolderUpdateFrequency);
        
        // loop through all files in the hot folder
        for (auto &file : std::filesystem::recursive_directory_iterator(hotFolderPath))
        {
            auto fileLastModificationTime = std::filesystem::last_write_time(file);
            string hotFolderfilePathStr = file.path().string();

            // check if file needs to be deleted
            if (file.path().filename().string().substr(0, fileDeleteKeyStr.size()).compare(fileDeleteKeyStr) == 0)
            {
                string deletedFileName = file.path().filename().string().substr(fileDeleteKeyStr.size());
                filesList.erase(std::filesystem::path(hotFolderPath + "/" + deletedFileName).make_preferred().string());

                std::filesystem::remove(file);
                m_logger->writeToLogFile(deletedFileName, Logger::Removed);

                std::filesystem::remove(std::filesystem::path(backupFolderPath + "/" + deletedFileName + ".bak").make_preferred().string());
                m_logger->writeToLogFile(deletedFileName + ".bak", Logger::Removed);
                continue;
            }

            // check for new file in the hotFolder and if found:
            // - add new file to the filesList 
            // - make a copy of the file to the backup folder
            if (!filesList.contains(hotFolderfilePathStr)) 
            {
                filesList[hotFolderfilePathStr] = fileLastModificationTime;
                string backupFolderFilePathStr = std::filesystem::path(backupFolderPath + "/" + file.path().filename().string() + ".bak").make_preferred().string();
                if (!std::filesystem::exists(backupFolderFilePathStr))
                {
                    m_logger->writeToLogFile(file.path().filename().string(), Logger::Created);
                    std::filesystem::copy(hotFolderfilePathStr, backupFolderFilePathStr);
                    m_logger->writeToLogFile(file.path().filename().string() + ".bak", Logger::BackedUp);
                }
            }
            else
            {
                // check if file was modified and if yes:
                // - change file modification time in the filesList
                // - update the backup file
                if (filesList[hotFolderfilePathStr] != fileLastModificationTime)
                {
                    filesList[hotFolderfilePathStr] = fileLastModificationTime;
                    string backupFolderFilePathStr = std::filesystem::path(backupFolderPath + "/" + file.path().filename().string() + ".bak").make_preferred().string();
                    std::filesystem::copy(
                        hotFolderfilePathStr, 
                        backupFolderFilePathStr, 
                        std::filesystem::copy_options::update_existing);
                    m_logger->writeToLogFile(file.path().filename().string(), Logger::Modified);
                    m_logger->writeToLogFile(file.path().filename().string() + ".bak", Logger::Modified);
                }
            }
        }
    }
}

void FileWatcher::createFolders(const string hotFolderPath, const string backupFolderPath)
{
    if (!std::filesystem::exists(hotFolderPath))
    {
        std::filesystem::create_directory(hotFolderPath);
    }

    if (!std::filesystem::exists(backupFolderPath))
    {
        std::filesystem::create_directory(backupFolderPath);
    }
}