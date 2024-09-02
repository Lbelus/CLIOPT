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

int count_env_var(char** env)
{
    size_t count = 0;
    while (*env != NULL)
    {
        count += 1;
        env += 1;
    }
    return count;
}

char** copy_env(char** env)
{
    size_t count = count_env_var(env);
    char** cpy_env = (char**)malloc(sizeof(char*) * count + 1);
    size_t index = 0;
    int len = 0;
    while (*env != NULL)
    {
        len = _my_strlen(*env);
        cpy_env[index] = (char*)malloc(sizeof(char) * (len + 1));
        _my_memcpy(cpy_env[index], *env, len + 1);
        env += 1;
        index += 1;
    }
    cpy_env[count] = NULL;
    return cpy_env;
}

int env(my_getopt_t* getopt_ptr, cmd_ptr_t* cf_ptr)
{
    char **env = cf_ptr->data;
    if (is_flag_active(getopt_ptr, 'l'))
    {
        printf("l is true");
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
    }
    else if (is_flag_active(getopt_ptr, 'u'))
    {
        printf("u is true\n");
    }
    else if (is_flag_active(getopt_ptr, 'd'))
    {
        printf("d is true\n");

    }   
    return EXIT_SUCCESS;
}

int rm_env_var(char** env_copy, const char* env_des)
{
    size_t len = _my_strlen(env_des);
    char **env = env_copy;
    while (*env)
    {
        if (_my_strncmp(*env, env_des, len) == 0 && (*env)[len] == '=')
        {
            free(*env);
            char** next = env;
            while (*next != NULL)
            {
                *next = *(next + 1);
                next += 1;
            }
            return EXIT_SUCCESS;
        }
        env++;
    }
    return EXIT_FAILURE;
}

int add_env_var(char** env_copy, const char* env_var)
{
    size_t count = count_env_var(env_copy) + 1;
    size_t len = _my_strlen(env_var);
    env_copy = realloc(env_copy, sizeof(char*) * count + 1);
    _my_memcpy(env_copy[count], env_var, len + 1);
    env_copy[count + 1] = NULL;
    return EXIT_SUCCESS;
}

int env_var_chr(char** env_copy, const char* env_des)
{
    size_t len = _my_strlen(env_des);
    char **env = env_copy;
    size_t pos = 0;
    while (*env)
    {
        if (_my_strncmp(*env, env_des, len) == 0 && (*env)[len] == '=')
        {
            return pos;
        }
        pos += 1;
        env++;
    }
    return -1;
}

int update_env(char** env_copy, const char* env_var)
{
    char* env_des = _my_strchr(env_var, '=');
    int index = 0;
    if (env_des == NULL)
    {
        return EXIT_FAILURE;
    }
    int len = _my_strlen(env_var);
    if ((index = env_var_chr(env_copy, env_des)) >= 0)
    {
        free(env_copy[index]);
        env_copy[index] = malloc(sizeof(char) * len + 1);
        _my_strcpy(env_copy[index], env_var);
    }
    else
    {
        add_env_var(env_copy, env_var);
    }
    return EXIT_SUCCESS;
}

void free_str_arr(char** str_arr)
{
    size_t index = 0;
    while (str_arr[index] != NULL)
    {
        free(str_arr[index]);
        index += 1;
    }
    free(str_arr);
}

void free_env_cpy(cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(_ENV_, cf_ptr->cmd) == 0)
        {
            free_str_arr((char**)cf_ptr->data);
        }
        cf_ptr++;
    }
}

int quit(my_getopt_t* getopt_ptr)
{
    getopt_ptr->exit_status = true;
    printf("quit cmd: exiting program\n");
    return EXIT_SUCCESS;
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
                if (_generic_fn(cf_ptr)(cf_ptr) == EXIT_SUCCESS)
                {
                    return EXIT_SUCCESS;
                }
                else
                {
                    return _generic_fn(getopt_ptr, cf_ptr)(getopt_ptr, cf_ptr);
                }
            }
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}