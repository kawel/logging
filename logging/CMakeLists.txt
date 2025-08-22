cmake_minimum_required(VERSION 3.25.0)

project(logging)

# Create the logging library
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/logging.c
)

# Public interface - what users of this library get
target_include_directories(${PROJECT_NAME}
    PUBLIC
        inc         # Public headers
)

# Library just provides the interface - no policy decisions


