#ifndef _FN_PTR_TYPE_
#define _FN_PTR_TYPE_

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

#endif
