#include <cli_cgetopt.h>

void    free_str_array( my_getopt_t *getopt_ptr);
int     flag_parser(int argc, const char** argv, const char* valid_args, my_getopt_t* getopt_ptr);
int     get_bit(bmp_t bmp, unsigned int index);
void    set_bitmap(bmp_t* bmp);

void init_getopt(my_getopt_t* getopt_ptr, const char* valid_args)
{
    getopt_ptr->exit_status = false;
    set_bitmap(getopt_ptr->bmp);
    getopt_ptr->nbr_str = 0;
    getopt_ptr->pos     = 0;
    getopt_ptr->index   = 1;
    getopt_ptr->str_pos = 0;
}

int cgetopt(int argc, const char** argv, const char* valid_args, my_getopt_t* getopt_ptr)
{
    int result = EXIT_FAILURE;
    if (argc <= 0)
    {
        return EXIT_FAILURE;
    }
    if (argv == NULL)
    {
        return EXIT_FAILURE;
    }
    if (valid_args == NULL)
    {
        return EXIT_FAILURE;
    }
    if (getopt_ptr == NULL)
    {
        return EXIT_FAILURE;
    }
    result = flag_parser(argc, argv, valid_args, getopt_ptr);
    return result;
}


const char** get_argv(const my_getopt_t* getopt_ptr)
{
    return getopt_ptr->argv;
}

int get_argc(const my_getopt_t* getopt_ptr)
{
    return getopt_ptr->argc;
}

int is_flag_active(const my_getopt_t* getopt_ptr, unsigned char ch)
{
    unsigned int index = (unsigned int)ch;
    unsigned int byte_index = index / 8;
    unsigned int bit_index = index % 8;
    int result = get_bit(getopt_ptr->bmp[byte_index], bit_index);
    return result;
}


void free_opt(my_getopt_t* getopt_ptr)
{
    free_str_array(getopt_ptr);
    if (getopt_ptr->nbr_str > 0)
    {
        free(getopt_ptr->str_arr);
    }
    free(getopt_ptr);
}