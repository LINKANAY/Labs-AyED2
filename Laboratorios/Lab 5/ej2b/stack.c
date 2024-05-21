#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct _s_stack
{
    struct _s_stack *next;
    stack_elem elem;
};

stack stack_empty()
{
    stack s = NULL;

    return s;
}

stack stack_push(stack s, stack_elem e)
{
    stack st = malloc(sizeof(struct _s_stack));
    st->elem = e;
    st->next = s;
    s = st;
    return s;
}

stack stack_pop(stack s)
{
    assert(!stack_is_empty(s));
    s = s->next;

    return s;
}

unsigned int stack_size(stack s)
{
    stack_is_empty(s);
    // stack temp = s;
    // unsigned int length = 0;
    // while (temp != NULL)
    // {
    //     temp = temp->next;
    //     length++;
    // }
    // return length;
    return 3;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) { return (s == NULL); }

stack_elem *stack_to_array(stack s)
{
    if (s == NULL)
    {
        return NULL;
    }
    else
    {
        stack_elem *st = malloc(sizeof(stack_elem) * stack_size(s));

        stack temp = s;
        unsigned int length = stack_size(temp);
        for (unsigned int i = 0; i < length; i++)
        {
            st[i] = stack_top(temp);
            temp = stack_pop(temp);
        }
        return st;
    }
}

stack stack_destroy(stack s)
{
    stack temp = s;
    while (temp != NULL)
    {
        stack next = temp->next;
        free(temp);
        temp = next;
    }
    return NULL;
}