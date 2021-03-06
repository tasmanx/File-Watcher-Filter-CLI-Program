#include "CLI.h"
#include "Logger.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <regex>
#include <fstream>

using namespace std;

const string SettingsFilename = "settings.txt";

void writeHotAndBacupFolderPathToSettingFile(string &hotFolderPath, string &backupFolderPath)
{
    ofstream file(SettingsFilename);
    file << hotFolderPath << endl;
    file << backupFolderPath << endl;
    file.close();
}

void readHotAndBacupFolderPathFromSettingFile(string &hotFolderPath, string &backupFolderPath)
{
    ifstream file(SettingsFilename);
    getline (file, hotFolderPath);
    getline (file, backupFolderPath);
    file.close();
}

void CLI::GetHotAndBackupFolderPaths(string &hotFolderPath, string &backupFolderPath)
{
    if (filesystem::exists(SettingsFilename))
    {
        readHotAndBacupFolderPathFromSettingFile(hotFolderPath, backupFolderPath);
    }
    else
    {
        cout << "Enter hot folder path: ";
        getline(cin, hotFolderPath);
        cout << "Enter backup folder path: ";
        getline(cin, backupFolderPath);

        hotFolderPath = filesystem::path(hotFolderPath).make_preferred().string();
        backupFolderPath = filesystem::path(backupFolderPath).make_preferred().string();

        writeHotAndBacupFolderPathToSettingFile(hotFolderPath, backupFolderPath);
    }
}

void printMenu()
{
    cout << "---Logs Filter Menu---" << endl;
    cout << " - To delete original and backup files rename file from hot folder with 'delete_' prefix" << endl;
    cout << " - To delete original and backup files at certain time rename file from hot folder with 'delete_yyyy-mm-dd HHmmss_' prefix" << endl;
    cout << " - To view all the logs type 'a'" << endl;
    cout << " - To filter logs by date or/and time type 'd'" << endl;
    cout << " - To filter logs by filename regex type 'r'" << endl;
    cout << " - To exit type 'x'" << endl;
}

template <typename Cont, typename Pred>
Cont filter(const Cont &container, Pred predicate) 
{
    Cont result;
    std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
    return result;
}

void printAllLogFiles(Logger *logger)
{
    for (auto const& logItem : logger->getFilesLogList())
    {
        cout << logItem.datetime << " "  << logItem.filename << " " << logItem.status << endl;
    } 
}

void printFilteredFilesByDateTime(Logger *logger)
{
    string inputDatetime;
    vector<Logger::LogData> filtered;

    cout << "Enter date or/and time (for example: '2021-10-10' or/and 20:20): ";
    getline(cin >> ws, inputDatetime);
    cout << endl;

    filtered = filter(logger->getFilesLogList(), [&](Logger::LogData logItem) { return logItem.datetime.find(inputDatetime) != string::npos; });
    for (auto const& logItem : filtered)
    {
        cout << logItem.datetime << " "  << logItem.filename << " " << logItem.status << endl;
    }
    cout << endl; 
}

void printFilteredFilesByFilenameRegex(Logger *logger)
{
    string inputRegex;
    vector<Logger::LogData> filtered;

    cout << "Enter filename regex (for example: '(.*)(.txt)'): ";
    getline(cin >> ws, inputRegex);
    cout << endl;

    filtered = filter(logger->getFilesLogList(), [&](Logger::LogData logItem) { return regex_match(logItem.filename, regex(inputRegex)); });
    for (auto const& logItem : filtered)
    {
        cout << logItem.datetime << " "  << logItem.filename << " " << logItem.status << endl;
    } 
    cout << endl;
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
            printAllLogFiles(logger);
            break;
        case 'd':
            printFilteredFilesByDateTime(logger);
            break;
        case 'r':
            printFilteredFilesByFilenameRegex(logger);
            break;
        case 'x':
            exit(0);
        default:
            cout << "No such command!" << endl;
            break;
        }
    }
}

