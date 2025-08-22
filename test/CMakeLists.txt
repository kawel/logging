cmake_minimum_required(VERSION 3.25.0)

project(test_main)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        test.c
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LIBRARY_LOG_LEVEL=LOG_WARN
        LIBRARY_LOG_NAME="[test main]"
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

