#include <cli_cgetopt.h>

int push(stack_t* stack, void* token)
{
    if (stack->top > MAX_INPUT_TOKENS) 
    {
        _my_write(2, OVERFLOW, SIZE_OVERFLOW);
        return EXIT_FAILURE;
    }
    stack->data[++stack->top] = token;
    return EXIT_SUCCESS;
}

void* pop(stack_t* stack)
{
    if (stack->top > MAX_INPUT_TOKENS)
    {
        _my_write(2, UNDERFLOW, SIZE_UNDERFLOW);
        return NULL;
    }
    return stack->data[stack->top--];
}

bool is_empty(stack_t* stack)
{
    if (stack->top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}