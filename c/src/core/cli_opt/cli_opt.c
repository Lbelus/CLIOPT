#include <common_header.h>

char* concat_string(int argc, ...)
{
    int len = 0;
    int index = 0;
    char* result = NULL;
	va_list ap;
    va_start(ap, argc);
    while (index < argc)
    {
        len += _my_strlen(va_arg(ap, char*));
        index += 1;
    }
    result = (char*)malloc(sizeof(char)* len + 1);
	_my_memset(result, '\0', len + 1);
    va_start(ap, argc);
    index = 0;
    while (index < argc)
    {
        _my_strcat(result, va_arg(ap, char*));
        index += 1;
    }
    return result;
}

int set_help(cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    char* cmd_str = NULL;
    char* map_str = malloc(1);
    map_str[0] = '\0'; // jank : this is not okay
    size_t size = 0;
    while (cf_ptr->cmd != NULL)
    {
        if (cf_ptr->description != NULL)
        {
            cmd_str = concat_string(6, 
                cf_ptr->cmd,
                " ",
                cf_ptr->flags,
                " ",
                cf_ptr->description,
                "\n"
            );
            size += _my_strlen(cmd_str) + 1;
            map_str = realloc(map_str, size);
            _my_strcat(map_str, cmd_str);
            free(cmd_str);
        }
        cf_ptr++;
    }
    map_str[size] = '\0';
    cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(_HELP_, cf_ptr->cmd) == 0)
        {
            cf_ptr->data = map_str;
            return EXIT_SUCCESS;
        }
        cf_ptr++;
    }
    return EXIT_FAILURE;
}

// int help(cmd_ptr_t* cf_ptr)
// {
//     while (cf_ptr->cmd != NULL)
//     {
//         if (_my_strcmp(_HELP_, cf_ptr->cmd) == 0)
//         {
//             printf("%s", (char*)cf_ptr->data);
//             fflush(stdout);
//             return EXIT_SUCCESS;
//         }
//         cf_ptr++;
//     }
//     return EXIT_FAILURE;
// }

int free_help(cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(_HELP_, cf_ptr->cmd) == 0)
        {
            free(cf_ptr->data);
            return EXIT_SUCCESS;
        }
        cf_ptr++;
    }
    return EXIT_FAILURE;
}

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
    free_env_cpy(cmd_ptr_map);
    free_help(cmd_ptr_map);
    return EXIT_SUCCESS;
}
