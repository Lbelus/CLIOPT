#include <cli_cgetopt.h>

void init_getopt(my_getopt_t* getopt_ptr, const char* valid_args)
{
    getopt_ptr->exit_status = false;
    getopt_ptr->bool_arr = (bool*)malloc(sizeof(bool) * _my_strlen(valid_args));
    fill_bool_array(getopt_ptr->bool_arr, _my_strlen(valid_args));
    getopt_ptr->nbr_str = 0;
    getopt_ptr->pos     = 0;
    getopt_ptr->index   = 1;
    getopt_ptr->str_pos = 0;
}