
/*
* Copyright 2025 Merit Automotive Electronic Systems S.L.U., All rights reserved
* It is not allowed to reproduce or utilize parts of this document in any form or by any means, including
* photocopying and microfilm, without permission in written by Merit Automotive Electronic Systems.
*/
#include <stdarg.h>
#include <stddef.h>

#include "logging.h"
#include "logging_levels.h"

int (*log_function)(const char *message, ...) = NULL;
static int logging_level = LOG_NONE;

static int default_log_function(const char *message, ...)
{
  (void)message;
//   (void)va_list;
    return 0;
}

void Logging_Init( int logging_level,  Logging_Function_t log_func )
{
    if(log_func)
    {
        log_function = log_func;
    }
    else
    {
        log_function = default_log_function;
    }

    if (logging_level <= LOG_DEBUG)
    {
        logging_level = logging_level;
    }
    else
    {
        logging_level = LOG_DEBUG;
    }
}
