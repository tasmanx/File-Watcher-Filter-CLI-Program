#include "CLI.h"
#include "Logger.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;

void CLI::GetHotAndBackupFolderPaths(string &hotFolderPath, string &backupFolderPath)
{
    cout << "Enter hot folder path: ";
    getline(cin, hotFolderPath);
    cout << "Enter backup folder path: ";
    getline(cin, backupFolderPath);

    hotFolderPath = filesystem::path(hotFolderPath).make_preferred().string();
    backupFolderPath = filesystem::path(backupFolderPath).make_preferred().string();
}

void printMenu()
{
    cout << "---Logs Filter Menu---" << endl;
    cout << " - To view all the logs type 'a'" << endl;
    cout << " - To filter logs by date or/and time type 'd'" << endl;
    cout << " - To filter logs by filename regex type 'r'" << endl;
    cout << " - To exit type 'x'" << endl;
}

void CLI::StartFilesFilter(Logger *logger)
{
    char menuSelectionInput;
    while (true)
    {
        printMenu(); 
        cin >> menuSelectionInput;
        switch (menuSelectionInput)
        {
        case 'a':
            for (auto const& logItem : logger->getFilesLogList())
            {
                cout << logItem.datetime << " "  << logItem.filename << " " << logItem.status << endl;
            } 
            break;
        case 'd':
            //todo
            break;
        case 'r':
            //todo
            break;
        case 'x':
            exit(0);
        default:
            cout << "No such command!" << endl;
            break;
        }
    }
}

