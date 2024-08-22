#include <common_header.h>

int main(int argc, char** argv)
{
    int             cmd_count   = 0;
    int             fd          = STDIN_FILENO;
    char*           str         = NULL;
    char**          tokens      = NULL;
    my_getopt_t*    getopt_ptr  = NULL;

    init_my_readline();
    while ((str = my_readline(fd)) != NULL)
    {
        getopt_ptr = malloc(sizeof(my_getopt_t));
        init_getopt(getopt_ptr, VALID_ARG);
        cmd_count = count_cmd(str);
        tokens = my_strtok(str , 1, __SPACE_CHAR__);
        flag_parser(cmd_count, tokens, VALID_ARG, getopt_ptr);
        execute_cmd(getopt_ptr);
        if (getopt_ptr->exit_status == true)
        {
            fd = -1;
        }
        free_opt(getopt_ptr);
        free(tokens);
        free(str);
    }
    return EXIT_SUCCESS;
}