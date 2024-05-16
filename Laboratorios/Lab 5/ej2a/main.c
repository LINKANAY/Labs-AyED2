#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int main(void)
{
    stack st = stack_empty();
    stack_push(st, 1);
    stack_pop(st);

    return EXIT_SUCCESS;
}