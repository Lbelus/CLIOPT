#ifndef _MY_CMD_HEADER_
#define _MY_CMD_HEADER_

#include <cli_cgetopt.h>
#include <cmd_type_enum.h>
#include <cli_cmd_type.h> 
#include <stdio.h>
#include <stdarg.h>

#define _QUIT_          "quit"
#define _DISPLAY_       "display"
#define _BIN_           "bin"

int     execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[]);
int     quit(my_getopt_t* getopt_ptr);

#include <cli_generic.h>

#endif
