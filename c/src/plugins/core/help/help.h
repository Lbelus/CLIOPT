#ifndef _HELP_HEADER_
#define _HELP_HEADER_

#include "../../../../include/cliopt/cgetopt.h"
#include "../../../../include/cmd_descriptor.h"
#include <stdarg.h>
#include <stdio.h>

#define _HELP_  "help"

/*  help funcs */
int     set_help(cmd_ptr_t cmd_ptr_map[]);
int     help(cmd_ptr_t* cf_ptr);
int     free_help(cmd_ptr_t cmd_ptr_map[]);

#endif
