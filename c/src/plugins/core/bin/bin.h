#ifndef _BIN_HEADER_
#define _BIN_HEADER_

#include "../../../../include/cliopt/parser.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#define PATH_MAX 4096
#define _PATH_STR_ "PATH"
#define _COLUMN_CHAR_   ':'

void cmd_or_exec(char** args, char** env);

#endif
