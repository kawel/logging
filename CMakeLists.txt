cmake_minimum_required(VERSION 3.25.0)

project(logging_test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        test/test.c
)



# Alternative approach - target-specific definitions
# target_compile_definitions(logging
#     PRIVATE
#         LIBRARY_LOG_LEVEL=LOG_INFO
#         LIBRARY_LOG_NAME="LOGGING_LIB"
#         LIBRARY_PRINT_FILE_PATH
# )

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LIBRARY_LOG_LEVEL=LOG_WARN
        LIBRARY_LOG_NAME="LOGGING_TEST"
        LIBRARY_PRINT_FILE_PATH
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        logging/inc
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logging
)

add_subdirectory(logging)

# czy to jest włąściwa struktura cmakelists