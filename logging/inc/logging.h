/*
* Copyright 2025 Merit Automotive Electronic Systems S.L.U., All rights reserved
* It is not allowed to reproduce or utilize parts of this document in any form or by any means, including
* photocopying and microfilm, without permission in written by Merit Automotive Electronic Systems.
*/

#ifndef LOGGING_H
#define LOGGING_H

#include "logging_cfg.h"
#include "logging_levels.h"
#include "logging_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*Logging_Function_t)(const char *message, ...);

void Logging_Init( int logging_level,  Logging_Function_t log_func );

#ifdef __cplusplus
}
#endif

#endif /* LOGGING_H */

