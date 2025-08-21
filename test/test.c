// test application to make use of the logging library
#include <string.h>

#include "logging.h"
// define logging function
static int custom_log_function(const char *message, ...)
{
    printf("Custom Log: %s\n", message, __VA_ARGS__);
    return 0;
}

int main(void)
{

    Logging_Init(LOG_DEBUG, custom_log_function);

    LogInfo("This is an info message");
    LogError("This is an error message");
    LogWarn("This is a warning message with some details %s", "additional info");
    LogDebug("This is a debug message with int: %d", 42);
    LogDebug("This is a debug message with float: %f", 3.14);
    LogDebug("This is a debug message with hex: %x", 0xDEAD);
    
    return 0;
}