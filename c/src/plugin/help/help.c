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

