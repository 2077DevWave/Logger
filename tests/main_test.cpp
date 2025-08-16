#include "../Logger.h"

void run_logger_tests() {
    Logger& logger = Logger::getInstance();
    logger.logToFile("tests/test_app.log");

    // Test 1: Test all log levels
    logger.setLogLevel(Logger::LogLevel::DEBUG);
    logger.debug("This is a debug message.");
    logger.info("This is an info message.");
    logger.warning("This is a warning message.");
    logger.error("This is an error message.");

    // Test 2: Test log level filtering
    logger.setLogLevel(Logger::LogLevel::WARNING);
    logger.debug("This debug message should be ignored.");
    logger.info("This info message should be ignored.");
    logger.warning("This is another warning message.");
    logger.error("This is another error message.");
}

int main() {
    run_logger_tests();
    return 0;
}
