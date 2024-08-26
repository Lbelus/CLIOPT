#include <common_header.h>

extern char *environ[];
int main(void)
{
    cmd_ptr_t command_descriptor[] = {
        {_HELP_,"-", "display help" , NULL, NULL},
        {_ENV_,"-", NULL , NULL, environ},
        {_DISPLAY_,"-", NULL, NULL, ">"},
        {_PRINT_FIRST_, "-laq", "it prints first", print_first, NULL},
        {_PRINT_SECOND_, "-laq","it prints second" , print_second, NULL},
        {_QUIT_,"-", "Exit the program safely" , quit, NULL},
        {NULL, NULL, NULL, NULL}
    };
    cliopt(command_descriptor);
    return EXIT_SUCCESS;
}