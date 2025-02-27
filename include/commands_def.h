#ifndef CMDS_DEF_HEADER_
#define CMDS_DEF_HEADER_


#define COMMANDS \
        /* One arg _GENERIC function with cmd_ptr_t */ \
        X(CMD_HELP,         "help",     "-",    "Display help",             NULL,            NULL) \
        /* Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t */ \
        X(CMD_ENV,          "env",      "-laud", "Display env",              NULL,            NULL) \
        /* Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t */ \
        X(CMD_BIN,          "bin",      "-",    "run bin file",             NULL,            NULL) \
        X(CMD_DISPLAY,      "display",  "-",    NULL,                       NULL,            ">") \
        /* standard function pointer with a getopt_t arg */ \
        X(CMD_PRINT_FIRST,  "ex1",      "-laq", "It prints first",          print_first,     NULL) \
        X(CMD_PRINT_SECOND, "ex2",      "-laq", "It prints second",         print_second,    NULL) \
        X(CMD_QUIT,         "quit",     "-",    "Exit the program safely",  quit,            NULL)
#endif
