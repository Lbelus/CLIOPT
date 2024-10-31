#ifndef _CMD_DESC_GEN_HEADER_
#define _CMD_DESC_GEN_HEADER_

// #ifndef _CMD_TYPE_ENUM_
// #define _CMD_TYPE_ENUM
// enum
// {
//     #define X(cmd_type, cmd_name, flags, description, func, data) cmd_type,
//     COMMANDS
//     #undef X
// };
// typedef enum cmd_type_t;
// #endif

#include <cmd_type_enum.h>

#ifndef _CMD_DESCR_
#define _CMD_DESCR_
// Generate command descriptor array
cmd_ptr_t command_descriptor[] = {
        #define X(cmd_type, cmd_name, flags, description, func, data) { cmd_type, cmd_name, flags, description, func, data },
        COMMANDS
        #undef X
        { 0, NULL, NULL, NULL, NULL, NULL }
};
#endif

#endif
