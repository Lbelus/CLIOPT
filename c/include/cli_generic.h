#ifndef _GENERIC_HEADER_
#define _GENERIC_HEADER_

#include "../src/plugin/env/env.h"
#include "../src/plugin/cmd/cmd.h"
#include "../src/plugin/example_cmd/example.h"
#include "../src/plugin/help/help.h"

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

#define __cmd1__(a) _Generic((a), \
    cmd_ptr_t*: help, \
    default: NULL \
)

#define __cmd2__(a, b) _Generic((a), \
    my_getopt_t*: env, \
    cmd_ptr_t*: env, \
    default: NULL \
)

#define __cmd3__(a, b, c) _Generic((a), \
    default: NULL \
)

#define __cmd4__(a, b, c, d) _Generic((a), \
    default: NULL \
)

#define _generic_fn(...) GET_MACRO(__VA_ARGS__, __cmd4__, __cmd3__,__cmd2__, __cmd1__)(__VA_ARGS__)



#endif
