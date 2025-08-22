cmake_minimum_required(VERSION 3.25.0)

project(test_main)

# Create the test executable
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        test.c
)

# Link to the logging library (gets its PUBLIC interface automatically)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logging
        test_module
)

# Application-specific logging configuration
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        LOGGING_LOG_NAME="TEST_APP"   # Custom name for test app
)
