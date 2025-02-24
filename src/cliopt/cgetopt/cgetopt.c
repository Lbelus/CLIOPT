#include "../../../include/cliopt/cgetopt.h"

static void count_str_array(int argc, const char** argv, my_getopt_t* getopt_ptr)
{
    int index = 1;
    while (index < argc)
    {
        if (argv[index][0] != __DASH_CHAR__)
        {
            getopt_ptr->nbr_str += 1;
        }
        index += 1;
    }
}

static void fill_bool_array(bool* bool_arr, int len)
{
    int index = 0;
    while (index < len)
    {
        bool_arr[index] = false;
        index += 1;
    }
}

void set_bitmap(bmp_t* bmp)
{
    for (int index = 0; index < BITMAP_SIZE; index++)
    {
        bmp[index].data =  0x00;
    }
}

static void set_bit(bmp_t* bmp, int index, int value)
{
    if (value)
    {
        bmp->data |= (1 << index);
    }
    else
    {
        bmp->data &= ~(1 << index);
    }
}

static void set_in_bmp(bmp_t* bmp, unsigned int index, int value)
{
    unsigned int bmp_index = index / 8;
    unsigned int bit_index = index % 8;

    set_bit(&bmp[bmp_index], bit_index, value);
}

int get_bit(const bmp_t bmp, unsigned int index)
{
    return (bmp.data >> index) & 1;
}

void flag_state(char opt, my_getopt_t *getopt_ptr, const char** argv)
{
    switch (opt)
    {
        case ':':
            _my_strcpy(getopt_ptr->str_arr[getopt_ptr->str_pos], argv[getopt_ptr->index]);
            getopt_ptr->str_pos += 1;
            getopt_ptr->index += 1;
            break;
        default:
            set_in_bmp(getopt_ptr->bmp, (unsigned int)opt, true);
    }
}

static void alloc_str_array(const char** argv, my_getopt_t *getopt_ptr)
{
    int index = 1;
    int pos = 0;
    while (pos < getopt_ptr->nbr_str)
    {
        if (argv[index][0] != __DASH_CHAR__)
        {
            getopt_ptr->str_arr[pos] = (char*)malloc(sizeof(char) * (_my_strlen(argv[index]) + 1));
            pos += 1;
        }
        index += 1;
    }
}

static const int opt_parser(const char** argv, const char* valid_args, my_getopt_t* getopt_ptr)
{
    if (argv[getopt_ptr->index][0] != __DASH_CHAR__)
    {
        return BADARG;
    }
    const char* opt = _my_strchr(valid_args, argv[getopt_ptr->index][getopt_ptr->pos]);
    if (opt == NULL || argv[getopt_ptr->index][getopt_ptr->pos] == '\0')
    {
        getopt_ptr->pos = 0;
        getopt_ptr->index += 1;
        return -1;
    }
    if (opt != NULL)
    {
        getopt_ptr->pos += 1;
        return opt[0];
    }
    else if (opt == NULL && argv[getopt_ptr->index][getopt_ptr->pos] != '\0')
    {
        if (argv[getopt_ptr->index][getopt_ptr->pos] != '\0' && argv[getopt_ptr->index][getopt_ptr->pos] == __DASH_CHAR__)
        {
            getopt_ptr->pos += 1;
            return 0;
        }
        else
        {
            getopt_ptr->pos += 1;
            return BADCHAR;
        }
    }
    return 0;
}

int flag_parser(int argc, const char** argv, const char* valid_args, my_getopt_t* getopt_ptr)
{
    getopt_ptr->argv = argv;
    getopt_ptr->argc = argc;
    int opt = 0;
    count_str_array(argc, argv, getopt_ptr);
    if (getopt_ptr->nbr_str > 0)
    {
        getopt_ptr->str_arr = (char**)malloc(sizeof(char*) * (getopt_ptr->nbr_str));
        alloc_str_array(argv, getopt_ptr);
    }
    else
    {
        return EXIT_FAILURE;
    }
    while (getopt_ptr->index < argc)
    {
        if ((opt = opt_parser(argv, valid_args, getopt_ptr)) != - 1)
        {
            flag_state(opt, getopt_ptr, argv);
        }
        opt = 0;
    }
    return EXIT_SUCCESS;
}

void free_str_array(my_getopt_t *getopt_ptr)
{
    int index = 0;
    while (index < getopt_ptr->nbr_str)
    {
        free(getopt_ptr->str_arr[index]);
        index += 1;
    }
}



