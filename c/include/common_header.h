#ifndef __MAIN_CLI_HEADERFILE_
#define __MAIN_CLI_HEADERFILE_

#include <stdlib.h>
#include <stdbool.h>

#include <cli_libasm.h>
#include <cli_readline.h>
#include <cli_parser.h>
#include <cli_cgetopt.h>
#include <cli_nstd.h>
#include <cli_cmd.h>
#include <cli_init.h>

int cliopt(cmd_ptr_t cmd_ptr_map[]);

#endif
