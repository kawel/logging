// Simple C++ test to verify extern "C" linkage works
#include <iostream>
#include "logging/inc/logging.h"

static int cpp_log_function(const char *message, ...)
{
    std::cout << "C++ Log: " << message << std::endl;
    return 0;
}

int main()
{
    std::cout << "C++ Test - Logging Version: " << Logging_GetVersion() << std::endl;
    
    Logging_Init(cpp_log_function);
    LogInfo("This is a C++ test message");
    
    return 0;
}
