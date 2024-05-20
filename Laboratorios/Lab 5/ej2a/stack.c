#include "stack.h"
#include <assert.h>
#include <stdlib.h>

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
    stack st = s;
    s = s->next;
    free(st);
    return s;
}

unsigned int stack_size(stack s)
{
    stack temp = s;
    unsigned int length = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        length++;
    }
    return length;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) { return (s == NULL); }

stack_elem *stack_to_array(stack s)
{
    stack_elem *st[stack_size(s)];
    stack temp = s;
    stack_elem i = 0;
    while (i < stack_size(s))
    {
        st[i] = malloc(sizeof(stack_elem) * stack_size(s));
        *st[i] = stack_top(temp);
        temp = temp->next;
        i++;
    }
    return *st;
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