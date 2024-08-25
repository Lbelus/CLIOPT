#ifndef _MY_CMD_FN_PTR_
#define _MY_CMD_FN_PTR_

#include <common_header.h>
#include <stdio.h>
#include <stdarg.h>

#define _PRINT_FIRST_ "PRINT_FIRST"
#define _PRINT_SECOND_ "PRINT_SECOND"
#define _QUIT_ "quit"
#define _HELP_ "help"
#define _ENV_ "ENV"

// #ifndef _ARGS_UNION_
// #define _ARGS_UNION_
// union args_union
// {
//     my_getopt_t* getopt_ptr,
//     cmd_ptr_t cmd_ptr_map[]
// };
// typedef union args_union args_union_t
// #endif

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    char* cmd;
    char* flags;
    char* description;
    int (*func_ptr)(my_getopt_t* getopt_ptr);
    void* data;
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

// #define GET_MACRO(_1,_2,NAME,...) NAME

#define user_defined_cmd1(a) _Generic((a), \
    cmd_ptr_t*: help, \
    int*: help, \
    default: NULL \
)

// #define user_defined_cmd2(a, b) _Generic((a), \
//     my_getopt_t*: help, \
//     cmd_ptr_t*: help \
// )(a, b)

// #define add(...) GET_MACRO(__VA_ARGS__, user_defined_cmd2, user_defined_cmd1)(__VA_ARGS__)

int set_help(cmd_ptr_t cmd_ptr_map[]);
int help(cmd_ptr_t* cf_ptr);
int free_help(cmd_ptr_t cmd_ptr_map[]);
int quit(my_getopt_t* getopt_ptr);
int print_first(my_getopt_t* getopt_ptr);
int print_second(my_getopt_t* getopt_ptr);
int execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[]);
char* select_flags(char* token, cmd_ptr_t cmd_ptr_map[]);

#endif