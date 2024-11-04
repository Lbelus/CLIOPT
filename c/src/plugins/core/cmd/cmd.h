#ifndef _MY_CMD_HEADER_
#define _MY_CMD_HEADER_

#include "../../../../include/cliopt/cgetopt.h"
#include "../../../../include/cliopt/cmd_type_enum.h"
#include "../../../../include/cliopt/cmd_descriptor.h"
#include <stdio.h>
#include <stdarg.h>

#define _QUIT_          "quit"
#define _DISPLAY_       "display"
#define _BIN_           "bin"

int     execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[]);
int     quit(my_getopt_t* getopt_ptr);

#include "../../../../include/generic.h"

#endif
