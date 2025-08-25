cmake_minimum_required(VERSION 3.25.0)

# Logging library example project that is demonstrating the logging functionality
# and how to use it within a project consisting of few modules.

project(logging_lib_TOP LANGUAGES C)

# Global project settings
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Global compile options (applied to all targets)
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

# Global logging configuration - common settings
add_compile_definitions(
    # File path options (choose one or leave commented for no file info):
    # LOGGING_DISABLED_GLOBALLY
    # LOGGING_PRINT_FILE_PATH           # Full file path (compile-time safe)
    
    # Function name support (optional - requires C99+ __func__ support)
    LOGGING_PRINT_FUNCTION_NAME       # Add function names to log messages
    
    LOGGING_TOP_LOG_LEVEL=LOG_DEBUG         # Project-wide default
)

# Add subdirectories in dependency order
add_subdirectory(logging)
add_subdirectory(example/test_module)
add_subdirectory(example/test_main)
