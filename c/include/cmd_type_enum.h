// cmd_type_enum.h
#ifndef CMD_TYPE_ENUM_H
#define CMD_TYPE_ENUM_H


#include <commands_def.h>

#ifndef _CMD_TYPE_ENUM_
#define _CMD_TYPE_ENUM
enum
{
    #define X(cmd_type, cmd_name, flags, description, func, data) cmd_type,
    COMMANDS
    #undef X
};
typedef enum cmd_type_t;
#endif

#endif
