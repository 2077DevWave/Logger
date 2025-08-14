#include "Logger.h"

int main() {
    // Get the singleton instance of the logger
    Logger& logger = Logger::getInstance();

    // Set the log level to DEBUG to see all messages
    logger.setLogLevel(Logger::LogLevel::DEBUG);

    // Log to a file
    logger.logToFile("app.log");

    // Log some messages
    logger.debug("This is a debug message.");
    logger.info("This is an info message.");
    logger.warning("This is a warning message.");
    logger.error("This is an error message.");

    // Change the log level to WARNING
    logger.setLogLevel(Logger::LogLevel::WARNING);

    // These messages will not be logged because their level is lower than WARNING
    logger.debug("This debug message will be ignored.");
    logger.info("This info message will be ignored.");

    // These messages will be logged
    logger.warning("This is another warning message.");
    logger.error("This is another error message.");

    return 0;
}