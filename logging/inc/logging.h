/*
 * @file: logging.h
 * @author: Paweł Kawula (pawel.kawula@kelectronics.pl)
 * -----
 * Copyright 2025 - KElectronics
 * -----
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdarg.h>

#include "logging_levels.h"
#include "logging_stack.h"

/* Version is automatically defined by CMake from project(logging VERSION x.y.z) */
#ifndef LOGGING_VERSION
#define LOGGING_VERSION "unknown"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int (*Logging_Function_t)(const char *message, ...);

    /**
     * @brief Initialize the logging system with a custom logging function.
     * 
     * @param log_func Pointer to the custom logging function.
     */
    void Logging_Init(Logging_Function_t log_func);

    /**
     * @brief Get the version of the logging library.
     * 
     * @return const char* Version string.
     */
    const char *Logging_GetVersion(void);

#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H */
