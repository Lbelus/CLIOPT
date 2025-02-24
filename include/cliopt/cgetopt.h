#ifndef __MY_GETOPT_H_
#define __MY_GETOPT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "./libasm.h"

#define BITMAP_SIZE 32

#ifndef _BITMAP_S_
#define _BITMAP_S_
struct bitmap_s
{
    unsigned char   data;
};
typedef struct bitmap_s bmp_t;
#endif

#ifndef STRUCT_MY_GETOPT
#define STRUCT_MY_GETOPT
typedef struct s_my_getopt
{
    int     index;
    int     pos;
    bmp_t   bmp[BITMAP_SIZE];
    int     nbr_str;
    int     str_pos;
    char**  str_arr;
    bool*   state;
    const char**  argv;
    int     argc;
    bool    exit_status;
} my_getopt_t;
#endif

#define _DISPLAY_               "display"
#define VALID_ARG               "-l"
#define BADCHAR                 (int)'?'
#define BADARG                  (int)':'
#define __STAR_CHAR__           '*'
#define __SPACE_CHAR__          ' '
#define __DASH_CHAR__           '-'

void            init_getopt(my_getopt_t* getopt_ptr, const char* valid_args);
int             cgetopt(int argc, const char** argv, const char* valid_args, my_getopt_t* getopt_ptr);
const char**    get_argv(const my_getopt_t* getopt_ptr);
int             get_argc(const my_getopt_t* getopt_ptr);
int             is_flag_active(const my_getopt_t* getopt_ptr, unsigned char ch);
void            free_opt(my_getopt_t* getopt_ptr);
const char**    get_long_args(const my_getopt_t* getopt_ptr);
int             get_long_arg_size(const my_getopt_t* getopt_ptr);

#endif
