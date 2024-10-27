#ifndef _HELP_HEADER_
#define _HELP_HEADER_

#include <cli_cgetopt.h>
#include <cli_cmd.h> 
#include <stdarg.h>
#include <stdio.h>

#define _HELP_  "help"

/*  help funcs */
int     set_help(cmd_ptr_t cmd_ptr_map[]);
int     help(cmd_ptr_t* cf_ptr);
int     free_help(cmd_ptr_t cmd_ptr_map[]);

#endif
