#include "Logger.h"

#include <filesystem>
#include <chrono>
#include <string>
#include <fstream> 
#include <sstream>

using namespace std;

const string Logger::Created = "Created";
const string Logger::BackedUp = "BackedUp";
const string Logger::Modified = "Modified";
const string Logger::Removed = "Removed";

Logger::Logger(string logFilename) : m_logFilename(logFilename)
{
    // fill m_filesLogList vector
    readFromLogFile();
}

string Logger::getCurrentDateTimeStr()
{
    auto n = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(n);
    tm buf;
    localtime_s(&buf, &in_time_t);
    stringstream ss;
    ss << put_time(&buf, "%Y-%m-%d %X");
    return ss.str();
}

void Logger::writeToLogFile(string filename, string status)
{
    string datetime = getCurrentDateTimeStr();
    m_filesLogList.emplace_back(datetime, filename, status);
    ofstream file(m_logFilename, ios::app);
    file << datetime << ";" << filename << ";" << status << endl;
    file.close();
}

void Logger::readFromLogFile()
{
    stringstream ss;
    string text;
    ifstream file(m_logFilename);
    while (getline (file, text)) {
        ss << text;
        string datetime, filename, status;
        getline( ss, datetime, ';' );
        getline( ss, filename, ';' );
        getline( ss, status, ';' );
        m_filesLogList.emplace_back(datetime, filename, status);
        ss.clear();
    }
    file.close();
}

vector<Logger::LogData> Logger::getFilesLogList()
{
    return m_filesLogList;
}