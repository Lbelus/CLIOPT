#include <common_header.h>

extern char **environ;
int main(void)
{
    command_descriptor[CMD_ENV].data = copy_env(environ);
    cliopt(command_descriptor);
    free_env_cpy(command_descriptor);
    return EXIT_SUCCESS;
}
