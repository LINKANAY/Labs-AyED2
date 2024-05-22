#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    stack s = stack_empty();
    s = stack_push(s, 1);
    s = stack_push(s, 2);
    s = stack_push(s, 3);
    s = stack_push(s, 5);
    s = stack_push(s, 4);

    unsigned int length = stack_size(s);
    for (unsigned int i = 0; i < length; i++)
    {
        printf("elem: %d\n", stack_top(s));
        s = stack_pop(s);
    }
    stack_destroy(s);
    
    return 0;
}