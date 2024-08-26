#include <common_header.h>


int print_first(my_getopt_t* getopt_ptr)
{
    (void)getopt_ptr;
    printf("first\n");
    return EXIT_SUCCESS;
}

int print_second(my_getopt_t* getopt_ptr)
{
    (void)getopt_ptr;
    printf("second\n");
    return EXIT_SUCCESS;
}

int quit(my_getopt_t* getopt_ptr)
{
    getopt_ptr->exit_status = true;
    printf("quit cmd: exiting program\n");
    return EXIT_SUCCESS;
}

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

int help(cmd_ptr_t* cf_ptr)
{
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(_HELP_, cf_ptr->cmd) == 0)
        {
            printf("%s", (char*)cf_ptr->data);
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        cf_ptr++;
    }
    return EXIT_FAILURE;
}

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
    return NULL;
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

int generic_ft(char* ft_designation, cmd_ptr_t cmd_ptr_map[])
{
    if (_my_strcmp(ft_designation, _HELP_) == 0)
    {
        cmd_ptr_t* cf_ptr = cmd_ptr_map;
        return user_defined_cmd1(cf_ptr)(cf_ptr);
    }
    return EXIT_FAILURE;
}


int execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(getopt_ptr->str_arr[0], cf_ptr->cmd) == 0)
        {
            if (cf_ptr->data == NULL)
            {
                return cf_ptr->func_ptr(getopt_ptr);
            }
            else
            {
                return generic_ft(getopt_ptr->str_arr[0], cmd_ptr_map); 
            }
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}