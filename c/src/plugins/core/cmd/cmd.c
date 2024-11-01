#include "./cmd.h"

/*  classic function pointer */
int quit(my_getopt_t* getopt_ptr)
{
    getopt_ptr->exit_status = true;
    printf("quit cmd: exiting program\n");
    return EXIT_SUCCESS;
}

/* Two arg generic function */
int execute_cmd(my_getopt_t* getopt_ptr, cmd_ptr_t cmd_ptr_map[])
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    printf("cmd_ptr_map[CMD_ENV]: %p\n", cmd_ptr_map[CMD_ENV]);
    printf("cmd_ptr_map[CMD_ENV]: %i\n", cmd_ptr_map[CMD_ENV].type);
    printf("cmd_ptr_map[CMD_ENV]: %p\n", cmd_ptr_map[CMD_ENV].data);
    char** env_ptr =  cf_ptr[CMD_ENV].data;
    printf("cmd_ptr_map[CMD_ENV]: %s\n", env_ptr[1]);
    printf("getopt str: %s\n", getopt_ptr->str_arr[0]);
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(getopt_ptr->str_arr[0], cf_ptr->cmd) == 0)
        {
            if (cf_ptr->data == NULL)
            {
                return cf_ptr->func_ptr(getopt_ptr); // run basic function ptr command
            }
            else
            {
                void* func = _generic_fn(cf_ptr);
                if (func != NULL) // run generic function with one argument (data)
                {
                    return _generic_fn(cf_ptr)(cf_ptr);
                }
                else
                {
                    void* func = _generic_fn(getopt_ptr, cf_ptr);                     
                    if (func == NULL)
                    {
                        printf("error func is null\n");
                    }
                    return _generic_fn(getopt_ptr, cf_ptr)(getopt_ptr, cf_ptr); // run generic function with two arguments
                }
            }
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}
