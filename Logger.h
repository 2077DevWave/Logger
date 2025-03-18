#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
public:
    enum class LogType {
        ERROR,
        WARNING,
        PROCESS
    };

    static void newLog(const std::string& message);
    static void newWarning(const std::string& message);
    static void newError(const std::string& message);

private:
    static void logMessage(LogType type, const std::string& message);
    static std::string getMessage(LogType type);
    static std::string currentTime();
};

#include "Logger.cpp"

#endif // LOGGER_H
