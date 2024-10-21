#include <common_header.h>

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
                return cf_ptr->func_ptr(getopt_ptr); // run normal command without passing data
            }
            else
            {
                if (_generic_fn(cf_ptr)(cf_ptr) == EXIT_SUCCESS) //
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
