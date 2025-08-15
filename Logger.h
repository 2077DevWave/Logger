#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

class Logger {
public:
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static Logger& getInstance();

    void setLogLevel(LogLevel level);
    void logToFile(const std::string& filename);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

    // New: async mode toggle
    void enableAsync(bool enable);

private:
    Logger();
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& message);
    std::string levelToString(LogLevel level);
    std::string getCurrentTime();

    // async members
    struct Message {
        LogLevel level;
        std::string text;
    };
    void asyncWorker();

    std::atomic<bool> asyncEnabled{false};
    std::thread worker;
    std::queue<Message> queue;
    std::mutex mtx;
    std::condition_variable cv;

    bool stopWorker{false};

    LogLevel currentLevel;
    std::ofstream logFile;
};

#endif // LOGGER_H
