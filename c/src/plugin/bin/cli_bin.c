#include "./cli_bin.h"


int env_var_chr(const char** env_copy, const char* env_des);
const char* get_env_var(const char** env_copy, const char* env_des);


void copy_from(char* dest, char* src, int* pos)
{
    int index = 0;
    while (src[index] != '\0')
    {
        dest[*pos] = src[index];
        *pos += 1;
        index +=1;
    }
}

void handle_flag(va_list ap, char* restrict* format, char* dest, int* pos)
{
    char* ptr = NULL;
    switch(*(*format))
    {
        case 's':
            ptr = va_arg(ap, char *);
            copy_from(dest, ptr, pos);
            (*format)++;
            break;
    }
}

void cpy_char(char* str, char* restrict* format, int* pos)
{
    str[*pos] = *(*format);
    *pos += 1;
    (*format)++;
}

int quick_snprintf(char *str, size_t size, char* restrict format, ...)
{
    int index = 0;
    va_list ap;
    va_start(ap, format);
    while (*format && index < size)
    {
        if (*format == '%')
        {
            format++;
            handle_flag(ap, &format, str, &index);
        } 
        else
        {
            cpy_char(str, &format, &index);
        }
    }
    va_end(ap);
    str[index] = '\0';
    return EXIT_SUCCESS;
}

/*
################ my_access_perm #################
# This function checks whether the given file path is accessible and executable.
# @return {int} Boolean indicating if the path is executable
*/
int my_access_perm(char *path)
{
    struct stat st;
    if (stat(path, &st) == 0)
    {
        if (st.st_mode & S_IXUSR)
        {
            return true;
        }
    }
    return false;
}

/*
################ find_exec_path #################
# This function searches for an executable in the directories specified in the path.
# @return {int} EXIT_SUCCESS if executable found, otherwise EXIT_FAILURE
*/
// need to recode strdup in asm
int find_exec_path(char* buff, const char* path, char* exec_name)
{
    int     index = 1;
    int     len = _my_strlen(path);
    char*   path_cpy = (char*)malloc(sizeof(char) * len + 1);
    
    path_cpy = _my_strcpy(path_cpy, path);
    char**  dir = my_strtok(path_cpy, 0, _COLUMN_CHAR_);
    while (dir[index] != NULL)
    {
        quick_snprintf(buff, PATH_MAX, "%s/%s", dir[index], exec_name);
        if (my_access_perm(buff))
        {
            free(path_cpy);
            free(dir);
            return EXIT_SUCCESS;
        }
        index += 1;
    }
    free(path_cpy);
    free(dir);
    return EXIT_FAILURE;
}

/*
################ my_access_f_ok #################
# This function checks whether the given file is accessible or not.
# @return {int} The return value of stat function
*/
int my_access_f_ok(char *pathname)
{
    struct stat buffer;
    int return_val = stat(pathname, &buffer);
    return return_val;
}

/*
################ check_exec #################
# This function checks whether the given argument is an executable.
# @return {bool} true if the argument is an executable, otherwise false
bool check_exec(char* args)
*/
bool check_exec(char* args)
{
    if (my_access_f_ok(args) == 0)
    {
        return true;
    }
    return false;
}

/*
################ exec_bin #################
# This function executes the binary executable from the given arguments.
# @return {int} Always returns EXIT_SUCCESS
*/
int exec_bin(char** args, char** env)
{
    int index = 0;
    pid_t pid = fork();
    char cmd_path[PATH_MAX];
    const char* path = get_env_var((const char**)env, _PATH_STR_);
    if (pid == 0)
    { /* child process */
        char **argv[] = {&args[1], NULL};
        find_exec_path(cmd_path, path, args[1]);
        execve(cmd_path, *argv, env);
        perror("cmd does not exist");
        exit(127); /* only if execv fails */
    }
    else
    { /* pid!=0; parent process */
        waitpid(pid, 0, 0); /* wait for child to exit */
    }
    return EXIT_SUCCESS;
}

/*
################ exec_file #################
# This function executes the file from the given arguments.
# @return {int} Always returns EXIT_SUCCESS
*/
int exec_file(char** args)
{
    int index = 0;
    char** new_env = NULL;
//    new_env = recreate_env();
    pid_t pid = fork();
    int status;

    if (pid == 0)
    { /* child process */
        char *argv[] = {args[1], NULL};
        execve(args[1], &args[1], new_env);
//        free_env(new_env);
        perror("cmd does not exist");
        exit(EXIT_FAILURE); /* only if execv fails */
    } 
    else
    { /* pid!=0; parent process */
        waitpid(pid, &status, 0); /* wait for child to exit */
        if (WIFSIGNALED(status) && WTERMSIG(status) == 11)
        {
//            segfault_msg();
        }
    }
//    free_env(new_env);
    return EXIT_SUCCESS;
}

/*
################ cmd_or_exec #################
# This function decides whether to execute a command or a binary file.
# @return {void}
*/
void cmd_or_exec(char** args, char** env)
{
    if (check_exec(args[1]))
    {
        exec_file(args);
    }
    else
    {
        exec_bin(args, env);
    }
}
