#ifndef __MAIN_CLI_HEADERFILE_
#define __MAIN_CLI_HEADERFILE_

#include <stdlib.h>
#include <stdbool.h>

#include "./cliopt/libasm.h"
#include "./cliopt/readline.h"
#include "./cliopt/parser.h"
#include "./cliopt/cgetopt.h"
#include "./cliopt/nstd.h"
#include "./cliopt/cmd_descriptor.h" 
#include "./cliopt/init.h"

int cliopt(cmd_ptr_t cmd_ptr_map[]);

#endif
