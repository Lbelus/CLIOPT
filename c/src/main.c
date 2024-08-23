#include <common_header.h>

int cliopt(cmd_ptr_t cmd_ptr_map[])
{
    int             cmd_count   = 1;
    int             fd          = STDIN_FILENO;
    char*           str         = NULL;
    char**          tokens      = NULL;
    my_getopt_t*    getopt_ptr  = NULL;

    init_my_readline();
    while ((str = my_readline(fd)) != NULL)
    {
        getopt_ptr = malloc(sizeof(my_getopt_t));
        init_getopt(getopt_ptr, VALID_ARG);
        tokens = my_strtok(str , &cmd_count, __SPACE_CHAR__);
        flag_parser(cmd_count, tokens, VALID_ARG, getopt_ptr);
        execute_cmd(getopt_ptr, cmd_ptr_map);
        if (getopt_ptr->exit_status == true)
        {
            fd = -1;
        }
        free_opt(getopt_ptr);
        free(tokens);
        free(str);
        cmd_count = 1;
    }
    return EXIT_SUCCESS;    
}

int main()
{
    cmd_ptr_t cmd_ptr_map[] = {
        {_PRINT_FIRST_, print_first},
        {_PRINT_SECOND_, print_second},
        {_QUIT_, quit},
        {NULL, NULL}
    };
    cliopt(cmd_ptr_map);
    return EXIT_SUCCESS;
}