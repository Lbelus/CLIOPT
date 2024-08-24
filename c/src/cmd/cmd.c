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

#include <string.h>

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
	result[0] = '\0';
    va_start(ap, argc);
    index = 0;
    while (index < argc)
    {
        strcat(result, va_arg(ap, char*));
        index += 1;
    }
    return result;
}

int map_len(cmd_ptr_t cmd_ptr_map[])
{
    size_t size         = 0;
    size_t index        = 0;
    cmd_ptr_t* cf_ptr   = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        size += _my_strlen(cf_ptr->cmd) + 1;
        size += _my_strlen(cf_ptr->flags) + 1 ;
        size += _my_strlen(cf_ptr->description) + 1;
        size += 4;
        cf_ptr++;
    }
    return size;
}

char* help(cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    char* cmd_str = NULL;
    char* map_str = malloc(1);
    map_str[0] = '\0'; // jank : this is not okay
    size_t size = 0;
    while (cf_ptr->cmd != NULL)
    {
        cmd_str = concat_string(6, 
        cf_ptr->cmd,
        " ",
        cf_ptr->flags,
        " ",
        cf_ptr->description,
        "\n"
        );
        size += _my_strlen(cmd_str) + 100;
        map_str = realloc(map_str, size);
        strcat(map_str, cmd_str);
        free(cmd_str);
        cf_ptr++;
    }
    return map_str;
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


int execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(getopt_ptr->str_arr[0], cf_ptr->cmd) == 0)
        {
            return cf_ptr->func_ptr(getopt_ptr);
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}