# Logger Library (C++)

A simple C++ logging library that provides functionality to log process messages, warnings, and errors with timestamped output. It also includes color formatting for warnings (yellow) and errors (red) using ANSI escape codes.

## Features
- Log process messages, warnings, and errors.
- Timestamped log messages.
- Color-coded output:
  - **Red** for errors.
  - **Yellow** for warnings.
  - **Default** for process logs.
- Simple API for easy integration.

## Installation
Clone the repository and include the `Logger.h` and `Logger.cpp` files in your project.

```sh
git clone https://github.com/2077DevWave/Logger.git
```

## Usage

Include the `Logger.h` file in your C++ project and use the static methods for logging.

### Example:
```cpp
#include "Logger.h"

int main() {
    Logger::newLog("Application started!");
    Logger::newWarning("This is a warning message!");
    Logger::newError("An error occurred!");
    return 0;
}
```

### Output:
```
[YYYY\MM\DD | HH:MM:SS] Process log: Application started
[YYYY\MM\DD | HH:MM:SS] Warning: This is a warning message   (in yellow)
[YYYY\MM\DD | HH:MM:SS] Error: An error occurred!   (in red)
```

## Files
- `Logger.h` - Header file defining the logging class.
- `Logger.cpp` - Implementation file for logging functions.

## License
This project is licensed under the MIT License.

## Contributing
Pull requests are welcome! Feel free to contribute improvements.

---

Made with ❤️ by [2077DevWave](https://github.com/2077DevWave)