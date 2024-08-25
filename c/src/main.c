#include <common_header.h>

extern char *environ[];
int main(void)
{
    cmd_ptr_t command_descriptor[] = {
        {_HELP_,"-", "display help" , NULL, NULL},
        {_ENV_,"-", NULL , NULL, environ},
        {_DISPLAY_,"-", "Text to display on the new line of your CLI" , NULL, ">"},
        {_PRINT_FIRST_, "-laq\0", "it prints first\0", print_first, NULL},
        {_PRINT_SECOND_, "-laq\0","it prints second\0" , print_second, NULL},
        {_QUIT_,"-\0", "Exit the program safely\0" , quit, NULL},
        {NULL, NULL, NULL, NULL}
    };
    cliopt(command_descriptor);
    return EXIT_SUCCESS;
}