#ifndef _INIT_HEADER_
#define _INIT_HEADER_

#include "../src/plugin/env/env.h"
#include "../src/plugin/cmd/cmd.h"
#include "../src/plugin/example_cmd/example.h"
#include "../src/plugin/help/help.h"



#define COMMANDS \
        /* One arg _GENERIC function with cmd_ptr_t */ \
        X(CMD_HELP,         "help",     "-",    "Display help",             NULL,            NULL) \
        /* Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t */ \
        X(CMD_ENV,          "env",      "-lud", "Display env",              NULL,            NULL) \
        /* Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t */ \
        X(CMD_BIN,          "bin",      "-",    "run bin file",             NULL,            NULL) \
        X(CMD_DISPLAY,      "display",  "-",    NULL,                       NULL,            ">") \
        /* standard function pointer with a getopt_t arg */ \
        X(CMD_PRINT_FIRST,  "ex1",      "-laq", "It prints first",          print_first,     NULL) \
        X(CMD_PRINT_SECOND, "ex2",      "-laq", "It prints second",         print_second,    NULL) \
        X(CMD_QUIT,         "quit",     "-",    "Exit the program safely",  quit,            NULL)

typedef enum
{
    #define X(cmd_type, cmd_name, flags, description, func, data) cmd_type,
    COMMANDS
    #undef X
} cmd_type_t;

#ifndef _CMD_DESCR_
#define _CMD_DESCR_
// Generate command descriptor array
cmd_ptr_t command_descriptor[] = {
        #define X(cmd_type, cmd_name, flags, description, func, data) { cmd_type, cmd_name, flags, description, func, data },
        COMMANDS
        #undef X
        { 0, NULL, NULL, NULL, NULL, NULL }
};

#endif


#endif
