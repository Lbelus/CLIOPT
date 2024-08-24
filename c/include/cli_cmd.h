#ifndef _MY_CMD_FN_PTR_
#define _MY_CMD_FN_PTR_

#include <common_header.h>
#include <stdio.h>
#include <stdarg.h>

#define _PRINT_FIRST_ "PRINT_FIRST"
#define _PRINT_SECOND_ "PRINT_SECOND"
#define _QUIT_ "quit"
#define _HELP_ "help"

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    char* cmd;
    char* flags;
    char* description;
    int (*func_ptr) (my_getopt_t*);
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

char* help(cmd_ptr_t cmd_ptr_map[]);
int quit(my_getopt_t* getopt_ptr);
int print_first(my_getopt_t* getopt_ptr);
int print_second(my_getopt_t* getopt_ptr);
int execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[]);
char* select_flags(char* token, cmd_ptr_t cmd_ptr_map[]);

#endif