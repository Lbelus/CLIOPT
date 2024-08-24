#include <common_header.h>

int cliopt(cmd_ptr_t cmd_ptr_map[])
{
    int             cmd_count   = 1;
    int             fd          = STDIN_FILENO;
    char*           str         = NULL;
    char**          tokens      = NULL;
    my_getopt_t*    getopt_ptr  = NULL;
    char* help_str = help(cmd_ptr_map);
    init_my_readline();
    while ((str = my_readline(fd)) != NULL)
    {
        getopt_ptr = malloc(sizeof(my_getopt_t));
        init_getopt(getopt_ptr, VALID_ARG);
        tokens = my_strtok(str , &cmd_count, __SPACE_CHAR__);
        if (_my_strcmp(tokens[1], _HELP_) == 0)
        {
            printf("%s", help_str);
        }
        else
        {
            char* valid_flags = select_flags(tokens[1], cmd_ptr_map);
            flag_parser(cmd_count, tokens, valid_flags, getopt_ptr);
            execute_cmd(getopt_ptr, cmd_ptr_map);
            if (getopt_ptr->exit_status == true)
            {
                fd = -1;
            }
        }
        free_opt(getopt_ptr);
        free(tokens);
        free(str);
        cmd_count = 1;
    }
    free(help_str);
    return EXIT_SUCCESS;    
}