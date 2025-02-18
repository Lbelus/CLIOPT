# CLIOPT

## Goals 

The goal of CLIOPT is to provide a platform upon which you can quickly setup a CLI, add or remove addon with custom types and arguments. 

Cliopt is plugin based. The plugins are separated into two categories:
	- Core -> Necessary to run the program but can be altered to fit your needs;
	- Addon -> Function or lib that you can freely add or remove ;

This way, you only have to focus on the core of your project and not on developing a full fledge CLI. So you only have to define the function you want to implement in a header following a template, cliopt will create all the necessary instruction in order to get your project running. 

## Usage

You'll find an example at ``src/plugins/addon/example_cmd/``

Create a new addon folder at ``src/plugins/addon/`` with a header file.


File to modify in order to add an addon:

Call the header in:
- ``include/plugins.h``

if you want to add a custom type:
- ``include/generic.h``

if you want to add a custom command:
- ``include/commands_def.h``

Command descriptor struct:

```c
	#ifndef _CMD_PTR_S_
	#define _CMD_PTR_S_
	struct cmd_ptr_s
	{
    		int type;
    		char* cmd;
    		char* flags;
    		char* description;
    		int (*func_ptr)(my_getopt_t* getopt_ptr);
    		void* data;
	};
	typedef struct cmd_ptr_s cmd_ptr_t;
	#endif
```



How to call it in your main;

#include <cliopt.h>


// if you want to make use of environment variable
extern char **environ;
int main(void)
{
    // make a copy of environment variables
    command_descriptor[CMD_ENV].data = (void*)copy_env(environ);
    
    // Call the CLI with your custom commands descriptor
    cliopt(command_descriptor);
    
    // free allocated elements; 
    free_env_cpy(command_descriptor);
    return EXIT_SUCCESS;
}


## Implementation 

Cliopt  is relying on generic programming in C to abstract the hassle of having to define and call you function from your CLI loop 

It also is implemented with custom light weight libs in c and assembly such as a getopt, readline, parser and lexer. 

Methods/topics : ``function pointers``, ``_Generic``, ``X_macros``, ``macros``. 

What are ``_Generic`` ? 

``_Generic`` are a form of beefed up ``typeof()`` coupled with a switch, they execute instructions based of a given type. It was introduced with C11 as an equivalent of template programing. 

They are not exactly macros because they are not entirely pre-processor instruction.

It can also be used for function overloading.


X macros are used in this implementation as way to quickly build an array of commands_descriptor. 

The commands descriptor :

```
        /* One arg _GENERIC function with cmd_ptr_t */ \
        X(CMD_HELP,         "help",     "-",    "Display help",             NULL,            NULL) \
        
        /* Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t */ \
        X(CMD_ENV,          "env",      "-lud", "Display env",              NULL,            NULL) \
        
        /* Two arg _GENERIC function with my_getopt_t* and cmd_ptr_t */ \
        X(CMD_BIN,          "bin",      "-",    "run bin file",             NULL,            NULL) \
        X(CMD_DISPLAY,      "display",  "-",    NULL,                       NULL,            ">") \
        
        /* standard function pointer with a getopt_t arg */ \
        X(CMD_PRINT_FIRST,  "ex1",      "-laq", "It prints first",          print_first,     NULL) \
        X(CMD_PRINT_SECOND, "ex2",      "-laq", "It prints second",         print_second,    NULL) \
        X(CMD_QUIT,         "quit",     "-",    "Exit the program safely",  quit,            NULL)
```

Links: 
	- https://www.chiark.greenend.org.uk/~sgtatham/quasiblog/c11-generic/
	- https://www.geeksforgeeks.org/_generic-keyword-c/

links : https://en.wikipedia.org/wiki/X_macro
