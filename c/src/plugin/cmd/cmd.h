#ifndef _MY_CMD_HEADER_
#define _MY_CMD_HEADER_

#include <cli_cgetopt.h>
#include <cli_cmd.h> 
#include <stdio.h>
#include <stdarg.h>

#define _QUIT_          "quit"
#define _DISPLAY_       "display"
#define _BIN_           "bin"

int     execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[]);
int     quit(my_getopt_t* getopt_ptr);

// #include <cli_init.h>  
#include <cli_generic.h>

// #define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

// #define __cmd1__(a) _Generic((a), \
//     cmd_ptr_t*: help, \
//     default: NULL \
// )

// #define __cmd2__(a, b) _Generic((a), \
//     my_getopt_t*: env, \
//     cmd_ptr_t*: env, \
//     default: NULL \
// )

// #define __cmd3__(a, b, c) _Generic((a), \
//     default: NULL \
// )

// #define __cmd4__(a, b, c, d) _Generic((a), \
//     default: NULL \
// )

// #define _generic_fn(...) GET_MACRO(__VA_ARGS__, __cmd4__, __cmd3__,__cmd2__, __cmd1__)(__VA_ARGS__)


#endif
