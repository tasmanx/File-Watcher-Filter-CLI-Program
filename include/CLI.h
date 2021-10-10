#ifndef CLI_H
#define CLI_H

#include <string>

class Logger;

namespace CLI {
    void GetHotAndBackupFolderPaths(std::string &hotFolderPath, std::string &backupFolderPath);
    void StartFilesFilter(Logger *logger);
};

#endif // CLI_H