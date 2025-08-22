cmake_minimum_required(VERSION 3.25.0)

project(test_module)

# Create the test executable
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/module.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        inc
)

# Link to the logging library (gets its PUBLIC interface automatically)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logging
)

# Application-specific logging configuration
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LOGGING_LOG_NAME="TEST_MODULE"   # Custom name for test module
        # LOGGING_TOP_LOG_LEVEL=LOG_INFO       # Custom log level for test module
)
