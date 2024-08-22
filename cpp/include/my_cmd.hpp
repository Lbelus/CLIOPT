#ifndef _MY_CMD_FN_PTR_
#define _MY_CMD_FN_PTR_

#include <functional> 
#include <my_custom_error.hpp>

#define _DO_            "DO"
#define _FOO_           "FOO"
#define _QUIT_          "QUIT"


#define _SOMETHING_     "SOMETHING"
#define _BAR_           "BAR"

class MyGetOpt;

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    const char* cmd;
    std::function<int(MyGetOpt&)> func_ptr;
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

int do_something(MyGetOpt& GetOptObj);
int Foo(MyGetOpt& GetOptObj);

int quit(MyGetOpt& GetOptObj);
int execute_cmd(MyGetOpt& GetOptObj);


#endif