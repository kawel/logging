cmake_minimum_required(VERSION 3.25.0)

project(logging)

add_library(${PROJECT_NAME} STATIC)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LIBRARY_LOG_LEVEL=LOG_INFO
        LIBRARY_LOG_NAME="LOGGING_LIB"
)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/logging.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        inc

)


