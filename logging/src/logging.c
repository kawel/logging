/**
 * @file: logging.c
 * @author:: Paweł Kawula (pawel.kawula@kelectronics.pl)
 * -----
 * Copyright 2025 - KElectronics
 */

#include <stdarg.h>
#include <stddef.h>

#include "logging.h"
#include "logging_levels.h"

int (*log_function)(const char *message, ...) = NULL;

static int default_log_function(const char *message, ...)
{
    (void)message;
    return 0;
}

void Logging_Init(Logging_Function_t log_func)
{
    if (log_func)
    {
        log_function = log_func;
    }
    else
    {
        log_function = default_log_function;
    }
}

const char *Logging_GetVersion(void)
{
    return LOGGING_VERSION;
}
