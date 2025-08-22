/**
 * @file: logging_stack.h  
 * @author: Paweł Kawula (pawel.kawula@kelectronics.pl)
 * @brief: High-performance embedded logging system with compile-time optimization
 * -----
 * Copyright 2025 - KElectronics
 * -----
 * @note: Core logging concepts inspired by FreeRTOS logging framework,
 *        but implementation completely rewritten for embedded performance
 */

#ifndef LOGGING_STACK_H
#define LOGGING_STACK_H

/* Include header for logging level macros. */
#include "logging_levels.h"

#define LOGGING_STRINGIZE(x) LOGGING_STRINGIZE2(x)
#define LOGGING_STRINGIZE2(x) #x
#define LOGGING_LINE_STRING LOGGING_STRINGIZE(__LINE__)

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
/* Check if LOGGING_LOG_NAME macro has been defined. */

#ifndef FILE_NAME
#define FILE_NAME ""
#endif

/* Pure compile-time string concatenation for maximum embedded performance */
#ifdef LOGGING_LOG_NAME
#ifdef LOGGING_PRINT_FILE_PATH
#define LOG_PREFIX "[" LOGGING_LOG_NAME "] (" __FILE__ ") "
#else
#define LOG_PREFIX "[" LOGGING_LOG_NAME "] "
#endif
#else
#ifdef LOGGING_PRINT_FILE_PATH
#define LOG_PREFIX "(" __FILE__ ") "
#else
#define LOG_PREFIX ""
#endif
#endif

/* Compile-time suffix when function names are NOT used */
#define LOG_SUFFIX ":" LOGGING_LINE_STRING " - "

/* Macro helpers for function name handling */
#ifdef LOGGING_PRINT_FUNCTION_NAME
/* Pass function name as separate argument to avoid runtime concatenation */
#define LOG_WITH_FUNC(level, message, ...) \
    SdkLog(level LOG_PREFIX "(%s)" LOG_SUFFIX message "\r\n", __func__, ##__VA_ARGS__)
#define LOG_WITHOUT_FUNC(level, message, ...) \
    LOG_WITH_FUNC(level, message, ##__VA_ARGS__)
#else
/* Pure compile-time concatenation when no function names */
#define LOG_WITH_FUNC(level, message, ...) \
    SdkLog(level LOG_PREFIX LOG_SUFFIX message "\r\n", ##__VA_ARGS__)
#define LOG_WITHOUT_FUNC(level, message, ...) \
    LOG_WITH_FUNC(level, message, ##__VA_ARGS__)
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
#if !defined(LOGGING_DISABLED_GLOBALLY)
#define SdkLog(message, ...) log_function(message, ##__VA_ARGS__)
#else
#define SdkLog(message, ...)
#endif

/**
 * Disable definition of logging interface macros when generating doxygen output,
 * to avoid conflict with documentation of macros at the end of the file.
 */
/* Check that LOGGING_TOP_LOG_LEVEL is defined and has a valid value. */
#if !defined(LOGGING_TOP_LOG_LEVEL) ||       \
    ((LOGGING_TOP_LOG_LEVEL != LOG_NONE) &&  \
     (LOGGING_TOP_LOG_LEVEL != LOG_ERROR) && \
     (LOGGING_TOP_LOG_LEVEL != LOG_WARN) &&  \
     (LOGGING_TOP_LOG_LEVEL != LOG_INFO) &&  \
     (LOGGING_TOP_LOG_LEVEL != LOG_DEBUG))
#error "Please define LOGGING_TOP_LOG_LEVEL as either LOG_NONE, LOG_ERROR, LOG_WARN, LOG_INFO, or LOG_DEBUG."
#else
#if LOGGING_TOP_LOG_LEVEL == LOG_DEBUG
/* All log level messages will logged. */
#define LogError(message, ...) LOG_WITH_FUNC("[ERROR] ", message, ##__VA_ARGS__)
#define LogWarn(message, ...) LOG_WITH_FUNC("[WARN]  ", message, ##__VA_ARGS__)
#define LogInfo(message, ...) LOG_WITH_FUNC("[INFO]  ", message, ##__VA_ARGS__)
#define LogDebug(message, ...) LOG_WITH_FUNC("[DEBUG] ", message, ##__VA_ARGS__)

#elif LOGGING_TOP_LOG_LEVEL == LOG_INFO
/* Only INFO, WARNING and ERROR messages will be logged. */
#define LogError(message, ...) LOG_WITH_FUNC("[ERROR] ", message, ##__VA_ARGS__)
#define LogWarn(message, ...) LOG_WITH_FUNC("[WARN]  ", message, ##__VA_ARGS__)
#define LogInfo(message, ...) LOG_WITH_FUNC("[INFO]  ", message, ##__VA_ARGS__)
#define LogDebug(message, ...)

#elif LOGGING_TOP_LOG_LEVEL == LOG_WARN
/* Only WARNING and ERROR messages will be logged.*/
#define LogError(message, ...) LOG_WITH_FUNC("[ERROR] ", message, ##__VA_ARGS__)
#define LogWarn(message, ...) LOG_WITH_FUNC("[WARN]  ", message, ##__VA_ARGS__)
#define LogInfo(message, ...)
#define LogDebug(message, ...)

#elif LOGGING_TOP_LOG_LEVEL == LOG_ERROR
/* Only ERROR messages will be logged. */
#define LogError(message, ...) LOG_WITH_FUNC("[ERROR] ", message, ##__VA_ARGS__)
#define LogWarn(message, ...)
#define LogInfo(message, ...)
#define LogDebug(message, ...)

#else /* if LOGGING_TOP_LOG_LEVEL == LOG_ERROR */

#define LogError(message, ...)
#define LogWarn(message, ...)
#define LogInfo(message, ...)
#define LogDebug(message, ...)

#endif /* if LOGGING_TOP_LOG_LEVEL == LOG_ERROR */
#endif /* if !defined( LOGGING_TOP_LOG_LEVEL ) || ( ( LOGGING_TOP_LOG_LEVEL != LOG_NONE ) && ( LOGGING_TOP_LOG_LEVEL != LOG_ERROR ) && ( LOGGING_TOP_LOG_LEVEL != LOG_WARN ) && ( LOGGING_TOP_LOG_LEVEL != LOG_INFO ) && ( LOGGING_TOP_LOG_LEVEL != LOG_DEBUG ) ) */

#endif /* ifndef LOGGING_STACK_H */
