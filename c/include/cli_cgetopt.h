#ifndef __MY_GETOPT_H_
#define __MY_GETOPT_H_

#include <stdlib.h>
#include <cli_libasm.h>
#include <stdbool.h>

#define MAX_INPUT_TOKENS 250
#define USE_TOKEN_QUEUE true
#define BITMAP_SIZE 32

#ifndef _BITMAP_S_
#define _BITMAP_S_
struct bitmap_s
{
    unsigned char   data;
};
typedef struct bitmap_s bmp_t;
#endif

#ifndef STACK_S
#define STACK_S
struct stack_s
{
    void* data[MAX_INPUT_TOKENS];
    int top;
};
typedef struct stack_s stack_t;
#endif

#define OVERFLOW "Stack is overflowing"
#define SIZE_OVERFLOW 20
#define UNDERFLOW "Stack is underflowing"
#define SIZE_UNDERFLOW 21

int     push(stack_t* stack, void* token);
void*   pop(stack_t* stack);
bool    is_empty(stack_t* stack);

#ifndef QUEUE_S
#define QUEUE_S
struct queue_s
{
    stack_t s1;
    stack_t s2;
    void* front;
    bool (*is_empty) (stack_t*);
    int (*push) (stack_t*, void*);
    void* (*pop) (stack_t*);
};
typedef struct queue_s queue_t;
#endif



int     enqueue(queue_t* queue, void* token);
void*   dequeue(queue_t* queue);
void*   peek(queue_t* queue);
bool    is_q_empty(queue_t* queue);
queue_t new_queue();


#ifndef STRUCT_MY_GETOPT
#define STRUCT_MY_GETOPT
typedef struct s_my_getopt
{
    int     index;
    int     pos;
    int     nbr_str;
    int     str_pos;
    char**  str_arr;
    bool*   state;
    bool    exit_status;
    bmp_t   bmp[BITMAP_SIZE];
    queue_t queue;
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