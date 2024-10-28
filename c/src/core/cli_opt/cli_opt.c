#include <stdlib.h>
#include <stdbool.h>
#include <cli_libasm.h>
#include <cli_readline.h>
#include <cli_parser.h>
#include <cli_cgetopt.h>
#include <cli_nstd.h>
#include <cli_cmd.h>
#include "../src/plugin/help/help.h"
#include "../src/plugin/cmd/cmd.h"

char* select_flags(char* token, cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(token, cf_ptr->cmd) == 0)
        {
            return cf_ptr->flags;
        }
        cf_ptr++;
    }
    return cf_ptr->flags;
}

char* set_display_text(cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(_DISPLAY_, cf_ptr->cmd) == 0)
        {
            return (char*)cf_ptr->data;
        }
        cf_ptr++;
    }
    return NULL;
}

void display_new_line(const char* str)
{
    printf("\r\033[K%s", str);
    fflush(stdout);
}

void init_cli(cmd_ptr_t cmd_ptr_map[], const char* display_text)
{
    set_help(cmd_ptr_map);
    init_my_readline();
    display_new_line(display_text);
}

char** opt_lex(my_getopt_t** getopt_ptr, char* str, cmd_ptr_t cmd_ptr_map[])
{
    int cmd_count = 1;
    char** tokens = NULL;
    *getopt_ptr = malloc(sizeof(my_getopt_t));
    tokens = my_strtok(str , &cmd_count, __SPACE_CHAR__);
    char* valid_flags = select_flags(tokens[1], cmd_ptr_map);
    init_getopt(*getopt_ptr, valid_flags);
    cgetopt(cmd_count, (const char**)tokens, valid_flags, *getopt_ptr);
    return tokens;
}

void free_opt_lex(char** tokens, my_getopt_t* getopt_ptr, char* str)
{
    free(tokens);
    free_opt(getopt_ptr);
    free(str);
}

int cliopt(cmd_ptr_t cmd_ptr_map[])
{
    int             fd              = STDIN_FILENO;
    char*           str             = NULL;
    char**          tokens          = NULL;
    my_getopt_t*    getopt_ptr      = NULL;
    char*           display_text    = set_display_text(cmd_ptr_map);
    init_cli(cmd_ptr_map, display_text);
    while ((str = my_readline(fd)) != NULL)
    {
        tokens = opt_lex(&getopt_ptr, str, cmd_ptr_map);
        execute_cmd(getopt_ptr, cmd_ptr_map);
        if (getopt_ptr->exit_status == true)
        {
            fd = -1;
        }
        free_opt_lex(tokens, getopt_ptr, str);
        display_new_line(display_text);
    }
    free_help(cmd_ptr_map);
    return EXIT_SUCCESS;
}
