#include <common_header.h>

cmd_ptr_t cmd_ptr_map[] = {
    {_PRINT_FIRST_, print_first},
    {_PRINT_SECOND_, print_second},
    {_QUIT_, quit},
    {NULL, NULL}
};

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

int execute_cmd(my_getopt_t* getopt_ptr)
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