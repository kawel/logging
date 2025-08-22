# Logging System Documentation

## Overview

This document describes the logging system used in the FATM application, based on FreeRTOS logging framework. The system provides four levels of logging with configurable output formats and customizable log transport mechanisms.

## Log Levels

The logging system supports four hierarchical log levels:

| Level | Value | Description |
|-------|-------|-------------|
| `LOG_NONE` | 0 | No log messages |
| `LOG_ERROR` | 1 | Erroneous application state or event |
| `LOG_WARN` | 2 | Abnormal event that may be indicative of an error |
| `LOG_INFO` | 3 | Helpful, informational message about normal execution |
| `LOG_DEBUG` | 4 | Detailed and excessive debug information |

## Configuration

The logging system is configured through CMake definitions in your `CMakeLists.txt` file. This approach ensures consistent configuration across all components.

### CMake Configuration Example

```cmake
# Global logging configuration - applies to all targets
add_compile_definitions(
    # Choose one of the following file path options:
    LIBRARY_PRINT_FILE_PATH          # Full file path
    # LIBRARY_PRINT_FILENAME_ONLY    # Just filename without path
    
    # Function name support (optional)
    LIBRARY_PRINT_FUNCTION_NAME      # Add function names to log messages
    
    LIBRARY_LOG_LEVEL=LOG_DEBUG      # Project-wide default log level
)

# Target-specific configuration (overrides global settings)
target_compile_definitions(my_app
    PRIVATE
        LIBRARY_LOG_NAME="[MY_APP]"   # Custom name for this target
)
```

### Configuration Options

#### File Path Display
Choose one of these options:
- **`LIBRARY_PRINT_FILE_PATH`** - Shows full file path (default)
- **`LIBRARY_PRINT_FILENAME_ONLY`** - Shows only filename without directory path
- **Neither** - No file information displayed

#### Function Name Display
- **`LIBRARY_PRINT_FUNCTION_NAME`** - Adds function names to log messages

#### Log Level Control
- **`LIBRARY_LOG_LEVEL=LOG_DEBUG`** - All messages (ERROR, WARN, INFO, DEBUG)
- **`LIBRARY_LOG_LEVEL=LOG_INFO`** - INFO and above (ERROR, WARN, INFO)
- **`LIBRARY_LOG_LEVEL=LOG_WARN`** - WARN and above (ERROR, WARN)
- **`LIBRARY_LOG_LEVEL=LOG_ERROR`** - ERROR only
- **`LIBRARY_LOG_LEVEL=LOG_NONE`** - No logging

#### Module/Library Name
- **`LIBRARY_LOG_NAME="[MODULE_NAME]"`** - Custom identifier for log messages

## API Usage

### Initialization
```c
#include "logging.h"

// Define your custom logging function
static int custom_log_function(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    vprintf(message, args);  // Output to stdout
    va_end(args);
    return 0;
}

int main(void) {
    // Initialize the logging system
    Logging_Init(LOG_DEBUG, custom_log_function);
    
    // Now you can use logging macros
    LogInfo("Application started");
    return 0;
}
```

## Example Output Formats

The output format depends on the configuration macros. Here are examples for different configurations:

### Configuration 1: With Library Name, No File Path
```cpp
#define LIBRARY_LOG_NAME "MyModule"
#define LIBRARY_LOG_LEVEL LOG_DEBUG
// LIBRARY_PRINT_FILE_PATH not defined
```

### Logging Macros
- **`LogError(message, ...)`** - Error level logging
- **`LogWarn(message, ...)`** - Warning level logging  
- **`LogInfo(message, ...)`** - Information level logging
- **`LogDebug(message, ...)`** - Debug level logging

### Example Usage
```c
LogError("Failed to initialize component %d", componentId);
LogWarn("Buffer usage at %d%% capacity", usage);
LogInfo("System initialized successfully");
LogDebug("Processing packet: size=%d, type=0x%02X", size, type);
```

## Output Format Examples

The output format depends on your configuration. Here are examples for different setups:

### Configuration 1: Full File Path + Function Names
```cmake
add_compile_definitions(
    LIBRARY_PRINT_FILE_PATH
    LIBRARY_PRINT_FUNCTION_NAME
    LIBRARY_LOG_LEVEL=LOG_DEBUG
)
target_compile_definitions(my_app PRIVATE LIBRARY_LOG_NAME="[APP]")
```

**Output:**
```
[ERROR] /home/user/project/src/main.c [APP] :42 main: Failed to initialize component 1
[WARN]  /home/user/project/src/main.c [APP] :43 main: Buffer usage at 85% capacity
[INFO]  /home/user/project/src/main.c [APP] :44 main: System initialized successfully
[DEBUG] /home/user/project/src/main.c [APP] :45 main: Processing packet: size=128, type=0x5A
```

### Configuration 2: Filename Only + Function Names
```cmake
add_compile_definitions(
    LIBRARY_PRINT_FILENAME_ONLY
    LIBRARY_PRINT_FUNCTION_NAME
    LIBRARY_LOG_LEVEL=LOG_DEBUG
)
target_compile_definitions(my_app PRIVATE LIBRARY_LOG_NAME="[APP]")
```

**Output:**
```
[ERROR] main.c [APP] :42 main: Failed to initialize component 1
[WARN]  main.c [APP] :43 main: Buffer usage at 85% capacity
[INFO]  main.c [APP] :44 main: System initialized successfully
[DEBUG] main.c [APP] :45 main: Processing packet: size=128, type=0x5A
```

### Configuration 3: Filename Only (No Function Names)
```cmake
add_compile_definitions(
    LIBRARY_PRINT_FILENAME_ONLY
    LIBRARY_LOG_LEVEL=LOG_INFO
)
target_compile_definitions(my_app PRIVATE LIBRARY_LOG_NAME="[APP]")
```

**Output:**
```
[ERROR] main.c [APP] :42 Failed to initialize component 1
[WARN]  main.c [APP] :43 Buffer usage at 85% capacity
[INFO]  main.c [APP] :44 System initialized successfully
// DEBUG message not shown (filtered out by LOG_INFO level)
```

### Configuration 4: Minimal Output
```cmake
add_compile_definitions(LIBRARY_LOG_LEVEL=LOG_WARN)
target_compile_definitions(my_app PRIVATE LIBRARY_LOG_NAME="[APP]")
```

**Output:**
```
[ERROR] [APP] :42 Failed to initialize component 1
[WARN]  [APP] :43 Buffer usage at 85% capacity
// INFO and DEBUG messages not shown (filtered out by LOG_WARN level)
```

### Configuration 5: Different Modules
```cmake
# Global settings
add_compile_definitions(
    LIBRARY_PRINT_FILENAME_ONLY
    LIBRARY_PRINT_FUNCTION_NAME
    LIBRARY_LOG_LEVEL=LOG_DEBUG
)

# Different names for different modules
target_compile_definitions(audio_module PRIVATE LIBRARY_LOG_NAME="[AUDIO]")
target_compile_definitions(network_module PRIVATE LIBRARY_LOG_NAME="[NET]")
target_compile_definitions(main_app PRIVATE LIBRARY_LOG_NAME="[APP]")
```

**Output from different modules:**
```
[INFO]  audio.c [AUDIO] :123 init_audio: Audio system initialized
[DEBUG] network.c [NET] :45 send_packet: Sending packet of size 256
[ERROR] main.c [APP] :67 main: Critical system failure
```

## Log Level Behavior

### LOG_DEBUG Level (Value: 4)
All messages are printed:
- ✅ LogError - Critical failures
- ✅ LogWarn - Warning conditions  
- ✅ LogInfo - General information
- ✅ LogDebug - Detailed debug information

### LOG_INFO Level (Value: 3)
Only INFO and above are printed:
- ✅ LogError - Critical failures
- ✅ LogWarn - Warning conditions
- ✅ LogInfo - General information
- ❌ LogDebug - (macro becomes empty)

### LOG_WARN Level (Value: 2)
Only WARN and above are printed:
- ✅ LogError - Critical failures
- ✅ LogWarn - Warning conditions
- ❌ LogInfo - (macro becomes empty)
- ❌ LogDebug - (macro becomes empty)

### LOG_ERROR Level (Value: 1)
Only ERROR messages are printed:
- ✅ LogError - Critical failures
- ❌ LogWarn - (macro becomes empty)
- ❌ LogInfo - (macro becomes empty)  
- ❌ LogDebug - (macro becomes empty)

### LOG_NONE Level (Value: 0)
No messages are printed:
- ❌ LogError - (macro becomes empty)
- ❌ LogWarn - (macro becomes empty)
- ❌ LogInfo - (macro becomes empty)
- ❌ LogDebug - (macro becomes empty)

## CMake Integration

### Project Structure Example

```
my_project/
├── CMakeLists.txt          # Top-level configuration
├── src/
│   ├── main.c
│   └── CMakeLists.txt
├── audio_module/
│   ├── audio.c
│   └── CMakeLists.txt
└── logging/                # Logging library
    ├── CMakeLists.txt
    ├── inc/
    │   ├── logging.h
    │   ├── logging_levels.h
    │   └── logging_stack.h
    └── src/
        └── logging.c
```

### Top-level CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.25.0)
project(my_project)

# Global logging settings
add_compile_definitions(
    LIBRARY_PRINT_FILENAME_ONLY
    LIBRARY_PRINT_FUNCTION_NAME
    LIBRARY_LOG_LEVEL=LOG_DEBUG
)

# Add subdirectories
add_subdirectory(logging)       # Library first
add_subdirectory(src)          # Applications second
add_subdirectory(audio_module)
```

### Module-specific CMakeLists.txt
```cmake
# src/CMakeLists.txt
add_executable(main main.c)
target_link_libraries(main PRIVATE logging)
target_compile_definitions(main PRIVATE LIBRARY_LOG_NAME="[MAIN]")

# audio_module/CMakeLists.txt  
add_library(audio audio.c)
target_link_libraries(audio PUBLIC logging)
target_compile_definitions(audio PUBLIC LIBRARY_LOG_NAME="[AUDIO]")
```

## Best Practices

1. **Use appropriate log levels:**
   - `LogError`: For critical failures that require immediate attention
   - `LogWarn`: For concerning conditions that don't stop execution
   - `LogInfo`: For general operational information
   - `LogDebug`: For detailed debugging information

2. **Include relevant context:**
   ```c
   LogError("Failed to open file '%s': errno=%d", filename, errno);
   LogInfo("Task started: priority=%d, stack=%d bytes", priority, stackSize);
   ```

3. **Use formatting efficiently:**
   ```c
   LogDebug("Buffer state: used=%d/%d bytes (%.1f%%)", used, total, percentage);
   ```

4. **Configure log levels appropriately:**
   - **Production builds:** `LOG_ERROR` or `LOG_WARN`
   - **Development builds:** `LOG_INFO` or `LOG_DEBUG`
   - **Testing builds:** `LOG_DEBUG`

5. **Use meaningful module names:**
   ```cmake
   target_compile_definitions(network PRIVATE LIBRARY_LOG_NAME="[NET]")
   target_compile_definitions(audio PRIVATE LIBRARY_LOG_NAME="[AUDIO]")
   target_compile_definitions(storage PRIVATE LIBRARY_LOG_NAME="[STORAGE]")
   ```

### Custom Log Transport

You can implement your own log transport function:

```c
#include <stdarg.h>
#include <stdio.h>

// Example: Log to file
static int file_log_function(const char *message, ...)
{
    static FILE *logfile = NULL;
    if (!logfile) {
        logfile = fopen("application.log", "a");
    }
    
    va_list args;
    va_start(args, message);
    vfprintf(logfile, message, args);
    fflush(logfile);
    va_end(args);
    return 0;
}

// Example: Log to syslog
static int syslog_function(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    vsyslog(LOG_INFO, message, args);
    va_end(args);
    return 0;
}

// Example: Log to multiple destinations
static int multi_log_function(const char *message, ...)
{
    va_list args1, args2;
    va_start(args1, message);
    va_copy(args2, args1);
    
    // Log to console
    vprintf(message, args1);
    
    // Log to file
    FILE *logfile = fopen("debug.log", "a");
    if (logfile) {
        vfprintf(logfile, message, args2);
        fclose(logfile);
    }
    
    va_end(args1);
    va_end(args2);
    return 0;
}

int main() {
    // Choose your transport
    Logging_Init(LOG_DEBUG, file_log_function);
    // or
    // Logging_Init(LOG_INFO, syslog_function);
    // or  
    // Logging_Init(LOG_DEBUG, multi_log_function);
    
    LogInfo("Application started with custom transport");
    return 0;
}
```

### Performance Considerations

- **Higher log levels generate more output** and impact performance
- **Use conditional compilation** for performance-critical code:
  ```c
  #if LIBRARY_LOG_LEVEL >= LOG_DEBUG
  LogDebug("Expensive debug operation: result=%d", expensive_calculation());
  #endif
  ```
- **Consider buffer sizes** when using extensive logging
- **Debug logging can significantly impact real-time behavior**
- Use `DISABLE_LOGGING` macro to completely disable all logging:
  ```cmake
  add_compile_definitions(DISABLE_LOGGING)
  ```

### Thread Safety

The logging system itself doesn't provide thread synchronization. If using in a multi-threaded environment, ensure your custom log function is thread-safe:

```c
#include <pthread.h>

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

static int thread_safe_log_function(const char *message, ...)
{
    pthread_mutex_lock(&log_mutex);
    
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    
    pthread_mutex_unlock(&log_mutex);
    return 0;
}
```

## Troubleshooting

### Common Issues

1. **"LogXXX function not found" errors**
   - Ensure `LIBRARY_LOG_LEVEL` is defined
   - Check that you're including `logging.h`
   - Verify CMake definitions are applied correctly

2. **No log output**
   - Check if `Logging_Init()` was called
   - Verify log level allows the messages you're trying to print
   - Ensure custom log function is implemented correctly

3. **Compilation errors with function names**
   - Make sure you're using C99 or later standard
   - `__func__` requires C99+ support

4. **CMake configuration not working**
   - Definitions must be set before `add_subdirectory()`
   - Use `target_compile_definitions()` for target-specific settings

---

*Updated on August 22, 2025*  
*Based on logging system v2.0 with CMake integration*
