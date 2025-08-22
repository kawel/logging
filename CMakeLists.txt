cmake_minimum_required(VERSION 3.25.0)

project(logging_test_TOP)

# Alternative approach - target-specific definitions
# target_compile_definitions(logging
#     PRIVATE
#         LIBRARY_LOG_LEVEL=LOG_INFO
#         LIBRARY_LOG_NAME="LOGGING_LIB"
#         LIBRARY_PRINT_FILE_PATH
# )

# target_compile_definitions(${PROJECT_NAME}
#     PRIVATE
#         LIBRARY_LOG_LEVEL=LOG_WARN
#         LIBRARY_LOG_NAME="[Logging app top]"
#         LIBRARY_PRINT_FILE_PATH
# )

# target_include_directories(${PROJECT_NAME}
#     PRIVATE
#         logging/inc
# )

# target_compile_options(${PROJECT_NAME}
#     PRIVATE
#         -Wall
#         -Wextra
#         -Wpedantic
#         -Werror
# )

add_subdirectory(logging)
add_subdirectory(test)
# add_subdirectory(test_module)
