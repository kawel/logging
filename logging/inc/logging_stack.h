/*
 * FreeRTOS V202104.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef LOGGING_STACK_H
#define LOGGING_STACK_H

/* Include header for logging level macros. */
#include "logging_levels.h"

/* Standard Include. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LOGGING_STRINGIZE(x) LOGGING_STRINGIZE2(x)
#define LOGGING_STRINGIZE2(x) #x
#define LOGGING_LINE_STRING LOGGING_STRINGIZE(__LINE__)

/* Macro to extract just the filename from __FILE__ - NOT USED in pure compile-time approach
 * Kept for reference but removed from implementation for maximum embedded performance
 */
#ifdef _WIN32
    #define LOGGING_FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define LOGGING_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

/**
 * @brief The name of the library or demo to add as metadata in log messages
 * from the library or demo.
 *
 * This metadata aids in identifying the module source of log messages.
 * The metadata is logged in the format `[ <LIBRARY-NAME> ]` as a prefix to the
 * log messages.
 * Refer to #LOG_METADATA_FORMAT for the complete format of the metadata prefix in
 * log messages.
 */
/* Check if LIBRARY_LOG_NAME macro has been defined. */

#ifndef FILE_NAME
#define FILE_NAME "" 
#endif

/* Pure compile-time string concatenation for maximum embedded performance */
#ifdef LIBRARY_LOG_NAME
    #ifdef LIBRARY_PRINT_FILE_PATH
        #define LOG_PREFIX "[" LIBRARY_LOG_NAME "] (" __FILE__ ") "
    #else
        #define LOG_PREFIX "[" LIBRARY_LOG_NAME "] "
    #endif
#else
    #ifdef LIBRARY_PRINT_FILE_PATH
        #define LOG_PREFIX "(" __FILE__ ") "
    #else
        #define LOG_PREFIX ""
    #endif
#endif

/* Function name support - optional for embedded systems */
#ifdef LIBRARY_PRINT_FUNCTION_NAME
    #define FUNCTION_SUFFIX "(" __func__ "):" LOGGING_LINE_STRING " - "
#else
    #define FUNCTION_SUFFIX ":" LOGGING_LINE_STRING " - "
#endif

extern int (*log_function)(const char *message, ...);

/**
 * @brief Common macro that maps all the logging interfaces,
 * (#LogDebug, #LogInfo, #LogWarn, #LogError) to the platform-specific logging
 * function.
 *
 * @note The default definition of the macro is an empty definition that does not
 * generate any logging.
 */
#if !defined( DISABLE_LOGGING )
    #define SdkLog( message, ...)  log_function(message, ##__VA_ARGS__)
#else
    #define SdkLog( message, ...)
#endif

/**
 * Disable definition of logging interface macros when generating doxygen output,
 * to avoid conflict with documentation of macros at the end of the file.
 */
/* Check that LIBRARY_LOG_LEVEL is defined and has a valid value. */
#if !defined(LIBRARY_LOG_LEVEL) ||       \
    ((LIBRARY_LOG_LEVEL != LOG_NONE) &&  \
     (LIBRARY_LOG_LEVEL != LOG_ERROR) && \
     (LIBRARY_LOG_LEVEL != LOG_WARN) &&  \
     (LIBRARY_LOG_LEVEL != LOG_INFO) &&  \
     (LIBRARY_LOG_LEVEL != LOG_DEBUG))
#error "Please define LIBRARY_LOG_LEVEL as either LOG_NONE, LOG_ERROR, LOG_WARN, LOG_INFO, or LOG_DEBUG."
#else
#if LIBRARY_LOG_LEVEL == LOG_DEBUG
/* All log level messages will logged. */
#define LogError(message, ...) SdkLog("[ERROR] " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogWarn(message, ...)  SdkLog("[WARN]  " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogInfo(message, ...)  SdkLog("[INFO]  " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogDebug(message, ...) SdkLog("[DEBUG] " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)

#elif LIBRARY_LOG_LEVEL == LOG_INFO
/* Only INFO, WARNING and ERROR messages will be logged. */
#define LogError(message, ...) SdkLog("[ERROR] " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogWarn(message, ...)  SdkLog("[WARN]  " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogInfo(message, ...)  SdkLog("[INFO]  " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogDebug(message, ...)

#elif LIBRARY_LOG_LEVEL == LOG_WARN
/* Only WARNING and ERROR messages will be logged.*/
#define LogError(message, ...) SdkLog("[ERROR] " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogWarn(message, ...)  SdkLog("[WARN]  " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogInfo(message, ...)
#define LogDebug(message, ...)

#elif LIBRARY_LOG_LEVEL == LOG_ERROR
/* Only ERROR messages will be logged. */
#define LogError(message, ...) SdkLog("[ERROR] " LOG_PREFIX FUNCTION_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LogWarn(message, ...)
#define LogInfo(message, ...)
#define LogDebug(message, ...)

#else /* if LIBRARY_LOG_LEVEL == LOG_ERROR */

#define LogError(message, ...)
#define LogWarn(message, ...)
#define LogInfo(message, ...)
#define LogDebug(message, ...)

#endif /* if LIBRARY_LOG_LEVEL == LOG_ERROR */
#endif /* if !defined( LIBRARY_LOG_LEVEL ) || ( ( LIBRARY_LOG_LEVEL != LOG_NONE ) && ( LIBRARY_LOG_LEVEL != LOG_ERROR ) && ( LIBRARY_LOG_LEVEL != LOG_WARN ) && ( LIBRARY_LOG_LEVEL != LOG_INFO ) && ( LIBRARY_LOG_LEVEL != LOG_DEBUG ) ) */

#endif /* ifndef LOGGING_STACK_H */
