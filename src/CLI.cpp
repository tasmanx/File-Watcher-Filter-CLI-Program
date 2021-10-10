#include <CLI.h>

#include <iostream>
#include <string>
#include <filesystem>

using std::string;
using std::cout;
using std::cin;
using std::endl;

void CLI::GetHotAndBackupFolderPaths(string &hotFolderPath, std::string &backupFolderPath)
{
    cout << "Enter hot folder path: ";
    getline(cin, hotFolderPath);
    cout << "Enter backup folder path: ";
    getline(cin, backupFolderPath);

    hotFolderPath = std::filesystem::path(hotFolderPath).make_preferred().string();
    backupFolderPath = std::filesystem::path(backupFolderPath).make_preferred().string();
}