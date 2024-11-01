# CLIOPT
i
## Goals 

The goal of CLIOPT is to provide a plateform upon which you can quickly setup a cli. 

Cliopt is plugin based. The plugins are separated into two categories:
	- Core -> Necessary to run the program but can be altered to fit your needs;
	- Addon -> Function or lib that you can freely add or remove ;

This way, you only have to focus on the core of your project and not on developing a full fledge CLI. So you only have to define the function you want to implement in a header following a template, cliopt will create all the necessary instruction in order to get your project running. 

## Usage

### step 1; 

After you have developped your addon. 

call the header in the init.h situated in include. 

## implementation 

Cliopt  is relying on generic programming in C to abstract the hassle of having to define and call you function from your CLI loop 

It also is implemented with custom light weight libs in c and assembly such as a getopt, readline, parser and lexer. 

methods/topics : command pointers, _Generic, X_macros, macros. 

What are _Generic ? 

_Generic are a form of beef up ``typeof()`` couples with a switch, they execute instructions based of a given type. It was introduced with C11 as an equivalent of template programing. 

They are not exactly macros because they are not entirely pre-processor instruction.

It can also be used for function overloading.


Links: 
	- https://www.chiark.greenend.org.uk/~sgtatham/quasiblog/c11-generic/
	- https://www.geeksforgeeks.org/_generic-keyword-c/

links : https://en.wikipedia.org/wiki/X_macro


