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
    LIBRARY_PRINT_FILE_PATH
    LIBRARY_LOG_LEVEL=LOG_DEBUG    # Project-wide default
)

# Add subdirectories in dependency order
add_subdirectory(logging)    # Library first (dependency)
add_subdirectory(test)       # Then applications that use it
# add_subdirectory(test_module)
