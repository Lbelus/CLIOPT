#ifndef _EXAMPLE_HEADER_
#define _EXAMPLE_HEADER_

#include <cli_cgetopt.h>
#include <cli_cmd.h> 
#include <stdio.h>

#define _PRINT_FIRST_   "ex1"
#define _PRINT_SECOND_  "ex2"

int     print_first(my_getopt_t* getopt_ptr);
int     print_second(my_getopt_t* getopt_ptr);

#endif
