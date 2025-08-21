# Logging System Documentation

## Overview

This document describes the logging system used in the FATM application, based on FreeRTOS logging framework. The system provides four levels of logging with configurable output formats and transport mechanisms.

## Log Levels

The logging system supports four hierarchical log levels:

| Level | Value | Description |
|-------|-------|-------------|
| `LOG_NONE` | 0 | No log messages |
| `LOG_ERROR` | 1 | Erroneous application state or event |
| `LOG_WARN` | 2 | Abnormal event that may be indicative of an error |
| `LOG_INFO` | 3 | Helpful, informational message about normal execution |
| `LOG_DEBUG` | 4 | Detailed and excessive debug information |

## Configuration Macros

### Core Configuration
- `LIBRARY_LOG_LEVEL` - Sets the maximum log level to be output
- `LIBRARY_LOG_NAME` - Library/module name to include in log messages
- `LIBRARY_PRINT_FILE_PATH` - Include full file path in log messages
- `FILE_NAME` - Custom file name override (defaults to empty string)

### Transport Configuration
The logging transport is configured in `logging_transport.h`:
```cpp
#define SdkLog( string, ...) com_send_const_str(&trace_com, string)
```

## Logging Macros

### Available Macros
- `LogError(message, ...)` - Error level logging
- `LogWarn(message, ...)` - Warning level logging  
- `LogInfo(message, ...)` - Information level logging
- `LogDebug(message, ...)` - Debug level logging

## Example Output Formats

The output format depends on the configuration macros. Here are examples for different configurations:

### Configuration 1: With Library Name, No File Path
```cpp
#define LIBRARY_LOG_NAME "MyModule"
#define LIBRARY_LOG_LEVEL LOG_DEBUG
// LIBRARY_PRINT_FILE_PATH not defined
```

**Example Code:**
```cpp
LogError("Failed to initialize component %d", componentId);
LogWarn("Buffer usage at %d%% capacity", usage);
LogInfo("System initialized successfully");
LogDebug("Processing packet: size=%d, type=0x%02X", size, type);
```

**Expected Output:**
```
[ERROR] MyModuleLine:45 Failed to initialize component 1
[WARN]  MyModuleLine:46 Buffer usage at 85% capacity  
[INFO]  MyModuleLine:47 System initialized successfully
[DEBUG] MyModuleLine:48 Processing packet: size=128, type=0x5A
```

### Configuration 2: With Library Name and File Path
```cpp
#define LIBRARY_LOG_NAME "AudioModule" 
#define LIBRARY_PRINT_FILE_PATH
#define LIBRARY_LOG_LEVEL LOG_INFO
```

**Example Code:**
```cpp
LogError("Audio codec initialization failed with error %d", errorCode);
LogWarn("Audio buffer underrun detected");
LogInfo("Audio stream started: rate=%dHz, channels=%d", sampleRate, channels);
LogDebug("Audio sample processed"); // This won't be printed (level too high)
```

**Expected Output:**
```
[ERROR] /path/to/audio.c AudioModule:123 Audio codec initialization failed with error -5
[WARN]  /path/to/audio.c AudioModule:124 Audio buffer underrun detected
[INFO]  /path/to/audio.c AudioModule:125 Audio stream started: rate=48000Hz, channels=2
```

### Configuration 3: No Library Name, With File Path
```cpp
#define LIBRARY_PRINT_FILE_PATH
#define LIBRARY_LOG_LEVEL LOG_WARN
// LIBRARY_LOG_NAME not defined
```

**Example Code:**
```cpp
LogError("Critical system failure");
LogWarn("Temperature threshold exceeded: %d°C", temperature);
LogInfo("Status update"); // This won't be printed (level too high)
LogDebug("Debug info"); // This won't be printed (level too high)
```

**Expected Output:**
```
[ERROR] /path/to/system.c:67 Critical system failure
[WARN]  /path/to/system.c:68 Temperature threshold exceeded: 85°C
```

### Configuration 4: Minimal Configuration
```cpp
#define LIBRARY_LOG_LEVEL LOG_ERROR
// No LIBRARY_LOG_NAME or LIBRARY_PRINT_FILE_PATH defined
```

**Example Code:**
```cpp
LogError("Memory allocation failed");
LogWarn("This won't be printed");
LogInfo("This won't be printed");  
LogDebug("This won't be printed");
```

**Expected Output:**
```
[ERROR] Line:101 Memory allocation failed
```

### Configuration 5: Custom File Name
```cpp
#define FILE_NAME "custom_module"
#define LIBRARY_LOG_NAME "TestLib"
#define LIBRARY_LOG_LEVEL LOG_DEBUG
// LIBRARY_PRINT_FILE_PATH not defined
```

**Example Code:**
```cpp
LogError("Test error message");
LogWarn("Test warning message");
LogInfo("Test info message");
LogDebug("Test debug message");
```

**Expected Output:**
```
[ERROR] TestLibcustom_module:200 Test error message
[WARN]  TestLibcustom_module:201 Test warning message
[INFO]  TestLibcustom_module:202 Test info message
[DEBUG] TestLibcustom_module:203 Test debug message
```

## Log Level Behavior

### LOG_DEBUG Level
All messages are printed:
- ✅ LogError
- ✅ LogWarn  
- ✅ LogInfo
- ✅ LogDebug

### LOG_INFO Level  
Only INFO and above are printed:
- ✅ LogError
- ✅ LogWarn
- ✅ LogInfo
- ❌ LogDebug (empty macro)

### LOG_WARN Level
Only WARN and above are printed:
- ✅ LogError
- ✅ LogWarn
- ❌ LogInfo (empty macro)
- ❌ LogDebug (empty macro)

### LOG_ERROR Level
Only ERROR messages are printed:
- ✅ LogError
- ❌ LogWarn (empty macro)
- ❌ LogInfo (empty macro)  
- ❌ LogDebug (empty macro)

### LOG_NONE Level
No messages are printed:
- ❌ LogError (empty macro)
- ❌ LogWarn (empty macro)
- ❌ LogInfo (empty macro)
- ❌ LogDebug (empty macro)

## Implementation Details

### Macro Expansion Examples

For `LIBRARY_LOG_LEVEL = LOG_DEBUG` and `LIBRARY_LOG_NAME = "MyLib"`:

```cpp
// This macro call:
LogError("Connection failed: %s", errorStr);

// Expands to:
SdkLog(("[ERROR] MyLibLine:" __LINE_STRING " Connection failed: %s" "\r\n"), errorStr);

// Which further expands to:
com_send_const_str(&trace_com, "[ERROR] MyLibLine:123 Connection failed: timeout\r\n");
```

### Transport Layer

The current transport implementation uses:
- `com_send_const_str(&trace_com, string)` - Sends log message via communication service
- Messages are terminated with `\r\n` 
- Uses trace communication channel

## Usage Guidelines

### Best Practices

1. **Use appropriate log levels:**
   - `LogError`: For critical failures that require immediate attention
   - `LogWarn`: For concerning conditions that don't stop execution
   - `LogInfo`: For general operational information
   - `LogDebug`: For detailed debugging information

2. **Include relevant context:**
   ```cpp
   LogError("Failed to open file '%s': errno=%d", filename, errno);
   LogInfo("Task started: priority=%d, stack=%d bytes", priority, stackSize);
   ```

3. **Use formatting efficiently:**
   ```cpp
   LogDebug("Buffer state: used=%d/%d bytes (%.1f%%)", used, total, percentage);
   ```

4. **Configure log levels appropriately:**
   - Production builds: `LOG_ERROR` or `LOG_WARN`
   - Development builds: `LOG_INFO` or `LOG_DEBUG`
   - Testing builds: `LOG_DEBUG`

### Performance Considerations

- Higher log levels generate more output and impact performance
- Use `LOG_NONE` for performance-critical sections
- Debug logging can significantly impact real-time behavior
- Consider buffer sizes when using extensive logging

---

*Generated on August 21, 2025*  
*File: SW_Components/logging/logging_stack.h*
