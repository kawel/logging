cmake_minimum_required(VERSION 3.25.0)

project(logging_test_TOP VERSION 1.0.0 LANGUAGES C)

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
    # LIBRARY_PRINT_FILE_PATH           # Full file path (compile-time safe)
    # (no option)                       # No file path information
    
    # Function name support (optional - requires C99+ __func__ support)
    # LIBRARY_PRINT_FUNCTION_NAME       # Add function names to log messages
    
    LIBRARY_LOG_LEVEL=LOG_DEBUG         # Project-wide default
)

# Add subdirectories in dependency order
add_subdirectory(logging)
add_subdirectory(test_module)
add_subdirectory(test_main)
