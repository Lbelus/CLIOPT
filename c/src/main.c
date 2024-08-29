#include <common_header.h>

extern char **environ;
int main(void)
{
    cmd_ptr_t command_descriptor[] = {
//        Function_name  |   FLAGS | Description               | Function ptr             | Data
//        char*              char*    char*                      int ft_ptr(my_getopt_t*)   void*
        { _HELP_,            "-",    "Display help" ,            NULL,                      NULL }, // One arg _GENERIC function with cmd_ptr_t|
        { _ENV_,             "-",    "Display env",              NULL,                      environ }, // Two arg _GENERIC function with cmd_ptr_t
        { _DISPLAY_,         "-",    NULL,                       NULL,                      ">" },
        { _PRINT_FIRST_,     "-laq\0", "It prints first",          print_first,               NULL }, // standard getopt_t function
        { _PRINT_SECOND_,    "-laq\0", "It prints second",         print_second,              NULL }, // standard getopt_t function
        { _QUIT_,            "-",    "Exit the program safely",  quit,                      NULL },
        { NULL,              NULL,   NULL,                       NULL,                      NULL }
    };
    cliopt(command_descriptor);
    return EXIT_SUCCESS;
}