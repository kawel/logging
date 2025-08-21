cmake_minimum_required(VERSION 3.25.0)

project(logging_test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        test/test.c
)

add_subdirectory(logging)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logging
)
