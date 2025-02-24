#include "./env.h"

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

char** add_env_var(char** env_copy, const char* env_var)
{
    size_t count = count_env_var(env_copy);
    size_t len = _my_strlen(env_var);
    env_copy = realloc(env_copy, sizeof(char*) * (count + 2));
    if (env_copy == NULL)
    {
        return NULL;
    }
    env_copy[count] = (char*)malloc(sizeof(char)* (len + 1)); 
    if (env_copy[count] == NULL)
    {
        return NULL;
    }
    _my_memcpy(env_copy[count], env_var, len + 1);
    env_copy[count + 1] = NULL;
    return env_copy;
}

char** rm_env_var(char** env_copy, const char* env_des)
{
    size_t len = _my_strlen(env_des);
    char **env = env_copy;
    size_t count = count_env_var(env_copy);
    while (*env)
    {
        if (_my_strncmp(*env, env_des, len - 1) == 0)
        {
            free(*env);
            char** next = env;
            while (*next != NULL)
            {
                *next = *(next + 1);
                next += 1;
            }
            env_copy = realloc(env_copy, sizeof(char*) * (count - 1));
            env_copy[count] = NULL;
            break;
        }
        env++;
    }
    return env_copy;
}

int env_var_chr(const char** env_copy, const char* env_des)
{
    size_t len = _my_strlen(env_des);
    const char **env = env_copy;
    size_t pos = 0;
    while (*env)
    {
        if (_my_strncmp(*env, env_des, len) == 0)
        {
            return pos;
        }
        pos += 1;
        env++;
    }
    return -1;
}

// char** update_env(char** env_copy, const char* env_var)
// {
//     char* env_des = _my_strchr(env_var, '=');
//     int index = 0;
//     if (env_des == NULL)
//     {
//         return NULL;
//     }
//     int len = _my_strlen(env_var);
//     index = env_var_chr((const char**)env_copy, env_des);
//     printf("index:%i\n", index);
//     if (index >= 0)
//     {
//         printf("here\n");
//         free(env_copy[index]);
//         env_copy[index] = malloc(sizeof(char) * len + 1);
//         _my_strcpy(env_copy[index], env_var);
//     }
//     else
//     {
//         env_copy = add_env_var(env_copy, env_var);
//     }
//     return env_copy;
// }

int indexof(const char* str, char ch)
{
    int index = 0;
    int len = _my_strlen(str);
    while (index < len)
    {
        if (str[index] == ch)
        {
            return index;
        }
        index += 1;
    }
    return -1;
}


char** update_env(char** env_copy, char* env_des)
{
    int pos = indexof(env_des, '=');
    if (pos == -1)
    {
        printf("environment variable is not defined\n");
        return env_copy;
    }
    size_t index = 0;
    int len = _my_strlen(env_des);
    while (env_copy[index] != NULL)
    {
        if (_my_strncmp(env_copy[index], env_des, pos) == 0)
        {
            free(env_copy[index]);
            env_copy[index] = malloc(sizeof(char) * len + 1);
            _my_strcpy(env_copy[index], env_des);
            return env_copy;
        }
        index += 1;
    }
    env_copy = add_env_var(env_copy, env_des);
    return env_copy;
}

int env(my_getopt_t* getopt_ptr, cmd_ptr_t* cf_ptr)
{
    char **env = cf_ptr->data;
    if (is_flag_active(getopt_ptr, 'l'))
    {
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
    }
    else if (is_flag_active(getopt_ptr, 'a'))
    {
        printf("a is true\n");
        const char** cpy_args = get_long_args(getopt_ptr);
        if (cpy_args[1] == NULL)
        {
            printf("Error: Missing environment argument");
            return EXIT_FAILURE;
        }
        else
        {
            printf("adding env var: %s\n", cpy_args[1]);
            cf_ptr->data = update_env(env, cpy_args[1]);
        }
    }
    else if (is_flag_active(getopt_ptr, 'd'))
    {
        printf("d is true\n");
        const char** cpy_args = get_long_args(getopt_ptr);
        if (cpy_args[1] == NULL)
        {
            printf("Error: Missing environment argument");
            return EXIT_FAILURE;
        }
        else
        {
            printf("rm var: %s\n", cpy_args[1]);
            cf_ptr->data = rm_env_var(env, cpy_args[1]);
        }
    }
    return EXIT_SUCCESS;
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


const char* get_env_var(const char** env_copy, const char* env_des)
{
    size_t pos = env_var_chr(env_copy, env_des);
    const char* env_ptr = env_copy[pos];
    return env_ptr;
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
