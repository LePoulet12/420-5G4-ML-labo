#include "activitylog.h"

#include <ctime>
#include <iomanip>
#include <iostream>

ActivityLog::ActivityLog(const std::filesystem::path& path)
    : file(path, std::ios::app) {
    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir le journal d'activités " << path << ".\n";
    }
}

void ActivityLog::record(const char* action, const std::string& bookDetails) {
    if (!file) {
        return;
    }
    const std::time_t now = std::time(nullptr);
    const std::tm* localTime = std::localtime(&now);
    if (!localTime) {
        std::cerr << "Erreur : impossible d'horodater l'activité.\n";
        return;
    }
    file << std::put_time(localTime, "%Y-%m-%d %H:%M:%S")
         << " - [" << action << "] " << bookDetails << '\n' << std::flush;
    if (!file) {
        std::cerr << "Erreur : impossible d'écrire dans le journal d'activités.\n";
    }
}
