[![C++ CI](https://github.com/2077DevWave/Logger/actions/workflows/test.yml/badge.svg)](https://github.com/2077DevWave/Logger/actions/workflows/test.yml)

# Logger Library (C++)

A simple yet powerful C++ logging library that provides functionality for log levels, timestamps, and file logging. It's designed as a singleton to ensure a single logging instance throughout your application.

## Features
- **Singleton Design:** Ensures a single, globally accessible logger instance.
- **Log Levels:** Supports `DEBUG`, `INFO`, `WARNING`, and `ERROR` levels.
- **File Logging:** Can be configured to write logs to a specified file.
- **Timestamped Messages:** Automatically adds a timestamp to each log entry.
- **Easy to Use:** Simple and intuitive API.

## Installation
Clone the repository and include the `Logger.h` and `Logger.cpp` files in your project.

```sh
git clone https://github.com/2077DevWave/Logger.git
```

## Usage

Include the `Logger.h` file in your C++ project. Get the logger instance and use its methods to log messages.

### Example:
```cpp
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

    return 0;
}
```

### Output (to console and `app.log`):
```
2025-08-14 10:30:00 [DEBUG] This is a debug message.
2025-08-14 10:30:00 [INFO] This is an info message.
2025-08-14 10:30:00 [WARNING] This is a warning message.
2025-08-14 10:30:00 [ERROR] This is an error message.
```

## API Reference

### `Logger& Logger::getInstance()`
Returns a reference to the singleton logger instance.

### `void setLogLevel(LogLevel level)`
Sets the minimum log level. Messages below this level will be ignored.
- `LogLevel::DEBUG`
- `LogLevel::INFO`
- `LogLevel::WARNING`
- `LogLevel::ERROR`

### `void logToFile(const std::string& filename)`
Enables logging to the specified file.

### `void debug(const std::string& message)`
Logs a `DEBUG` level message.

### `void info(const std::string& message)`
Logs an `INFO` level message.

### `void warning(const std::string& message)`
Logs a `WARNING` level message.

### `void error(const std::string& message)`
Logs an `ERROR` level message.

## Files
- `Logger.h` - Header file defining the logging class.
- `Logger.cpp` - Implementation file for logging functions.
- `test.cpp` - Example usage.

## License
This project is licensed under the MIT License.
