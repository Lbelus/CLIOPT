#ifndef _MY_CMD_FN_PTR_
#define _MY_CMD_FN_PTR_

#include <main_header.h>
#include <stdio.h>

#define _PRINT_FIRST_ "PRINT_FIRST"
#define _PRINT_SECOND_ "PRINT_SECOND"
#define _QUIT_ "QUIT"

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    char* cmd;
    int (*func_ptr) (my_getopt_t*);
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

int print_first(my_getopt_t* getopt_ptr);
int print_second(my_getopt_t* getopt_ptr);
int quit(my_getopt_t* getopt_ptr);
int execute_cmd(my_getopt_t* getopt_ptr);

#endif