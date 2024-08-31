#ifndef __MY_GETOPT_H_
#define __MY_GETOPT_H_

#include <stdlib.h>
#include <cli_libasm.h>
#include <stdbool.h>

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
    bool    exit_status;
} my_getopt_t;
#endif


#define VALID_ARG "-l"
#define BADCHAR                 (int)'?'
#define BADARG                  (int)':'
#define __STAR_CHAR__           '*'
#define __SPACE_CHAR__          ' '
#define __DASH_CHAR__           '-'

void    count_str_array(int argc, char** argv, my_getopt_t* getopt_ptr);
void    alloc_str_array(char** argv, my_getopt_t *getopt_ptr);
void    free_str_array( my_getopt_t *getopt_ptr);
void    dynamic_free(int argc, char** argv, my_getopt_t *getopt_ptr);
void    fill_bool_array(bool* bool_arr, int len);
int     flag_parser(int argc, char** argv, const char* valid_args, my_getopt_t* getopt_ptr);
void    free_str_array( my_getopt_t *getopt_ptr);
void    free_opt(my_getopt_t* getopt_ptr);
void    set_bitmap(bmp_t* bmp);
void    init_getopt(my_getopt_t* getopt_ptr, const char* valid_args);
int     my_getopt(char** argv, const char* valid_args, my_getopt_t* getopt_ptr);
void    flag_state(char opt, my_getopt_t *getopt_ptr, char** argv);
int     is_flag_active(my_getopt_t* getopt_ptr, unsigned char ch);

#endif