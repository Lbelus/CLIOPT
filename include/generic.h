#ifndef _GENERIC_HEADER_
#define _GENERIC_HEADER_


#include "./cliopt/cmd_type_enum.h"
#include "./plugins.h"

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME

#define __cmd1__(a) _Generic((a), \
    cmd_ptr_t*:     a->type == CMD_HELP ? help:\
                    NULL, \
    default: NULL \
)

#define __cmd2__(a, b) _Generic((a), \
    my_getopt_t*:   (b != NULL && b->type == CMD_ENV) ? env : NULL, \
    cmd_ptr_t*:     (b != NULL && b->type == CMD_ENV) ? env : NULL, \
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
