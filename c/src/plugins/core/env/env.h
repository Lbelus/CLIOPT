#ifndef _ENV_HEADER_
#define _ENV_HEADER_

#include <cli_cgetopt.h>
#include <cli_cmd_type.h> 
#include <stdio.h>


#define _ENV_ "env"

/* environment funcs */
int             env(my_getopt_t* getopt_ptr, cmd_ptr_t* cf_ptr);
char**          copy_env(char** env);
void            free_env_cpy(cmd_ptr_t cmd_ptr_map[]);
const char*     get_env_var(const char** env_copy, const char* env_des);


#endif
