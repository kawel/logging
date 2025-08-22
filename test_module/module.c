#include <stdarg.h>

#include <stdio.h>
#include <string.h>

#include "logging.h"

static int custom_log_function(const char *message, ...)
{
    va_list args;
    va_start(args, message);

    vprintf(message, args);
    
    va_end(args);
    return 0;
}

void testfunction(void)
{
    Logging_Init(LOG_DEBUG, custom_log_function);
    // Test function implementation
    LogInfo("This is an info message");
    LogError("This is an error message");
    LogWarn("This is a warning message with some details %s", "additional info");
    LogDebug("This is a debug message with int: %d", 42);
    LogDebug("This is a debug message with float: %f", 3.14);
    LogDebug("This is a debug message with hex: 0x%x", 0xDEAD);

}