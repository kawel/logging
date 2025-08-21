cmake_minimum_required(VERSION 3.25.0)

project(logging_test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        test/test.c
)

add_subdirectory(logging)

# Add include directories for the logging library
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
