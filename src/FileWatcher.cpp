#include "FileWatcher.h"

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>

using std::string;
using std::unordered_map;

FileWatcher::FileWatcher()
{

}

void FileWatcher::startFileWatcher(const string hotFolderPath, const string backupFolderPath)
{
    // create hot and backup folders if needed
    createFolders(hotFolderPath, backupFolderPath);

    std::chrono::duration<int, std::milli> hotFolderUpdateFrequency = std::chrono::milliseconds(1000);
    unordered_map<string, std::filesystem::file_time_type> filesList;

    while (true)
    {
        std::this_thread::sleep_for(hotFolderUpdateFrequency);
        
        // loop through all files in the hot folder
        for (auto &file : std::filesystem::recursive_directory_iterator(hotFolderPath))
        {
            auto fileLastModificationTime = std::filesystem::last_write_time(file);
            string hotFolderfilePathStr = file.path().string();

            // check for new file in the hotFolder and if found:
            // - add new file to the filesList 
            // - make a copy of the file to the backup folder
            if (!filesList.contains(hotFolderfilePathStr)) 
            {
                filesList[hotFolderfilePathStr] = fileLastModificationTime;

                string backupFolderFilePathStr = std::filesystem::path(backupFolderPath + "/" + file.path().filename().string() + ".bak").make_preferred().string();
                if (!std::filesystem::exists(backupFolderFilePathStr))
                {
                    std::filesystem::copy(hotFolderfilePathStr, backupFolderFilePathStr);
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