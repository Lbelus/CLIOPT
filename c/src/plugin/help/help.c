#include <common_header.h>

int help(cmd_ptr_t* cf_ptr)
{
    while (cf_ptr->cmd != NULL)
    {
        if (_my_strcmp(_HELP_, cf_ptr->cmd) == 0)
        {
            printf("%s", (char*)cf_ptr->data);
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        cf_ptr++;
    }
    return EXIT_FAILURE;
}
