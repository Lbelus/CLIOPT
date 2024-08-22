#include <main_header.hpp>


/*
    ################ cmd ptr map #################
    # store function ptr and matching keywords
*/
cmd_ptr_t cmd_ptr_map[] = {
    {_DO_,              do_something},
    {_FOO_,             listEntry},
    {_QUIT_,            quit},
    {NULL,              nullptr}
};

/*
    ################ check arg count #################
    # check arg count
    # check if arg count stored in getopt struct match
    # trow a a custom error and write to STDERR if condition is met
    # @return {int}
*/
void checkArgCount(int nb_args, int expected)
{
    if (nb_args < expected)
    {
        throw ArgError("Missing argument");
    }
}

/*
    ################ add entry #################
    # check arg count
    # add concrete product to factory or std::string to vector
    # @return {int}
*/
int do_something(MyGetOpt& GetOptObj)
{
    char** args = GetOptObj.getArgs();
    const std::string cmd = args[1];
    if (cmd == _SOMETHING_)
    {
        std::cout << _SOMETHING_ << std::endl;
    }
    return EXIT_SUCCESS;
}

/*
    ################ create Bd #################
    # Factory Method Design Pattern
    # CreateBook() is extended into the subclasses, 
    # calling the CreateBook() in BookCreator will invoke the FactoryMethod. 
    # add a new bd() to library
    # @return {int}
*/
int FOO(MyGetOpt& GetOptObj)
{
    char** args = GetOptObj.getArgs();
    const std::string cmd = args[1];
    if (cmd == _BAR_)
    {
        std::cout << _BAR_ << std::endl;
    }
    return EXIT_SUCCESS;
}

/*
    ################ quit #################
    # match function ptr prototype
    # @return {int}
*/
int quit(MyGetOpt& GetOptObj,  std::shared_ptr<Library> library)
{
    (void)library;
    GetOptObj.setExit();
    std::cout << "quit cmd: exiting program" << std::endl;
    return EXIT_SUCCESS;
}

/*
    ################ execute_cmd #################
    # Iterate over map until match and execute corresponding function ptr;
    # @return {int}
*/
int execute_cmd(MyGetOpt& GetOptObj,  std::shared_ptr<Library> library)
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {    
        if (_my_strcmp(GetOptObj.getKeyword(), cf_ptr->cmd) == 0)
        {
            try
            {
                return cf_ptr->func_ptr(GetOptObj, library);
            }
            catch (const std::exception& error)
            {
                std::cerr << error.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}