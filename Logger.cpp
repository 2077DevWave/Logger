#include "Logger.h"
#include <sstream>
#include <iostream>
#include <atomic>

Logger::Logger() : currentLevel(LogLevel::INFO), asyncEnabled(false), stopWorker(false) {}

Logger::~Logger()
{
    // Stop async worker if running
    if (asyncEnabled)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stopWorker = true;
        }
        cv.notify_all();
        if (worker.joinable())
            worker.join();
    }
    if (logFile.is_open())
    {
        logFile.close();
    }
}

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::setLogLevel(LogLevel level)
{
    currentLevel = level;
}

void Logger::logToFile(const std::string &filename)
{

    if (logFile.is_open())
    {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
}
void Logger::debug(const std::string &message) { log(LogLevel::DEBUG, message); }
void Logger::info(const std::string &message) { log(LogLevel::INFO, message); }
void Logger::warning(const std::string &message) { log(LogLevel::WARNING, message); }
void Logger::error(const std::string &message) { log(LogLevel::ERROR, message); }
void Logger::log(LogLevel level, const std::string &message)
{
    if (level >= currentLevel)
    {
        std::string logMessage = getCurrentTime() + " [" + levelToString(level) + "] " + message;
        if (asyncEnabled)
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                queue.push({level, logMessage});
            }
            cv.notify_one();
        }
        else
        {
            std::cout << logMessage << std::endl;
            if (logFile.is_open())
            {
                logFile << logMessage << std::endl;
            }
        }
    }
}
void Logger::asyncWorker()
{
    while (true)
    {
        Message msg;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]
                    { return stopWorker || !queue.empty(); });
            if (stopWorker && queue.empty())
                break;
            msg = queue.front();
            queue.pop();
        }
        // write outside lock
        // logMessage already contains timestamp and level, just use it directly
        std::string logMessage = msg.text;
        std::cout << logMessage << std::endl;
        if (logFile.is_open())
        {
            logFile << logMessage << std::endl;
        }
    }
}
std::string Logger::levelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
std::string Logger::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void Logger::enableAsync(bool enable)
{
    if (enable && !asyncEnabled)
    {
        asyncEnabled = true; // start worker
        stopWorker = false;
        worker = std::thread(&Logger::asyncWorker, this);
    }
    else if (!enable && asyncEnabled)
    { // disable: flush and stop
        {
            std::lock_guard<std::mutex> lock(mtx);
            stopWorker = true;
        }
        cv.notify_all();
        if (worker.joinable())
            worker.join();
        asyncEnabled = false;
    }
}