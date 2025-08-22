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

#define LOGGING_VERSION "1.1.0"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int (*Logging_Function_t)(const char *message, ...);

    void Logging_Init(Logging_Function_t log_func);
    const char *Logging_GetVersion(void);

#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H */
