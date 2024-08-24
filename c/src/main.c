#include <common_header.h>



int main()
{
    cmd_ptr_t cmd_ptr_map[] = {
        // {_HELP_,"-", "display help" , help},
        {_PRINT_FIRST_, "-laq\0", "it prints first\0", print_first},
        {_PRINT_SECOND_, "-laq\0","it prints second\0", print_second},
        {_QUIT_,"-\0", "Exit the program safely\0" , quit},
        {NULL, NULL, NULL, NULL}
    };
    cliopt(cmd_ptr_map);
    return EXIT_SUCCESS;
}