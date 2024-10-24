#include <common_header.h>

extern char **environ;
int main(void)
{
    cmd_ptr_t command_descriptor[] = {
//        Function_name  |   FLAGS | Description               | Function ptr             | Data
//        char*              char*    char*                      int ft_ptr(my_getopt_t*)   void*
        { _HELP_,            "-",    "Display help" ,            NULL,                      NULL }, // One arg _GENERIC function with cmd_ptr_t
        { _ENV_,             "-lud", "Display env",              NULL,                      copy_env(environ) }, // Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t
        { _BIN_,             "-lud", "Display env",              NULL,                      NULL }, // Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t
        { _DISPLAY_,         "-",    NULL,                       NULL,                      ">" },
        { _PRINT_FIRST_,     "-laq", "It prints first",          print_first,               NULL }, // standard getopt_t function
        { _PRINT_SECOND_,    "-laq", "It prints second",         print_second,              NULL }, // standard getopt_t function
        { _QUIT_,            "-",    "Exit the program safely",  quit,                      NULL },
        { NULL,              "-",    NULL,                       NULL,                      NULL } // NULL terminator
    };
    cliopt(command_descriptor);
    free_env_cpy(command_descriptor);
    return EXIT_SUCCESS;
}
