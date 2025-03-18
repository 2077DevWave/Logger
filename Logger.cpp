#include "Logger.h"

void Logger::newLog(const std::string& message) {
    logMessage(LogType::PROCESS, message);
}

void Logger::newWarning(const std::string& message) {
    logMessage(LogType::WARNING, message);
}

void Logger::newError(const std::string& message) {
    logMessage(LogType::ERROR, message);
}

void Logger::logMessage(LogType type, const std::string& message) {
    std::string color_code;
    switch (type) {
        case LogType::ERROR: color_code = "\033[31m"; break; // Red
        case LogType::WARNING: color_code = "\033[33m"; break; // Yellow
        default: color_code = "\033[0m"; // Reset
    }

    std::string prefix = currentTime() + " " + getMessage(type) + message + "\n";
    std::cout << color_code << prefix << "\033[0m";
    std::cout.flush();
}

std::string Logger::getMessage(LogType type) {
    switch (type) {
        case LogType::ERROR: return "Error: ";
        case LogType::WARNING: return "Warning: ";
        case LogType::PROCESS: return "Process log: ";
        default: return "";
    }
}

std::string Logger::currentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm buf;
    localtime_r(&in_time_t, &buf);
    std::ostringstream ss;
    ss << "[" << buf.tm_year + 1900 << "\\" << buf.tm_mon + 1 << "\\" << buf.tm_mday 
       << " | " << std::setw(2) << std::setfill('0') << buf.tm_hour << ":"
       << std::setw(2) << std::setfill('0') << buf.tm_min << ":"
       << std::setw(2) << std::setfill('0') << buf.tm_sec << "]";
    return ss.str();
}
