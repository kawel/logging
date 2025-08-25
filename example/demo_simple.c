/**
 * @brief Demo showing different logging configuration options
 */

#include <stdio.h>
#include <stdarg.h>
#include "logging.h"

// Custom logging function that shows the features
static int custom_log_function(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    return 0;
}

int main(void)
{
    printf("=== Logging Configuration Demo ===\n\n");
    
    Logging_Init(LOG_DEBUG, custom_log_function);

    printf("1. With LIBRARY_PRINT_FILENAME_ONLY + LOGGING_PRINT_FUNCTION_NAME:\n");
    LogInfo("This is an info message");
    LogError("This is an error message");
    LogWarn("This is a warning message with details: %s", "extra info");
    LogDebug("This is a debug message with number: %d", 42);
    
    return 0;
}
