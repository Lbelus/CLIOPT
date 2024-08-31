#include <common_header.h>



void display_new_line(const char* str)
{
    printf("\r\033[K%s", str);
    fflush(stdout);
}

int cliopt(cmd_ptr_t cmd_ptr_map[])
{
    int             cmd_count       = 1;
    int             fd              = STDIN_FILENO;
    char*           str             = NULL;
    char**          tokens          = NULL;
    my_getopt_t*    getopt_ptr      = NULL;
    char*           display_text    = set_display_text(cmd_ptr_map);
    set_help(cmd_ptr_map);
    init_my_readline();
    display_new_line(display_text);
    while ((str = my_readline(fd)) != NULL)
    {
        getopt_ptr = malloc(sizeof(my_getopt_t));
        tokens = my_strtok(str , &cmd_count, __SPACE_CHAR__);
        char* valid_flags = select_flags(tokens[1], cmd_ptr_map);
        init_getopt(getopt_ptr, valid_flags);
        flag_parser(cmd_count, tokens, valid_flags, getopt_ptr);
        execute_cmd(getopt_ptr, cmd_ptr_map);
        if (getopt_ptr->exit_status == true)
        {
            fd = -1;
        }
        free_opt(getopt_ptr);
        free(tokens);
        free(str);
        cmd_count = 1;
        display_new_line(display_text);
    }
    free_env_cpy(cmd_ptr_map);
    free_help(cmd_ptr_map);
    return EXIT_SUCCESS;
}