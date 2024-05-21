#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack
{
    stack_elem *elems;     // Arreglo de elementos
    unsigned int size;     // Cantidad de elementos en la pila
    unsigned int capacity; // Capacidad actual del arreglo elems
};

stack stack_empty()
{
    stack s = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e)
{
    if (s == NULL)
    {
        s = malloc(sizeof(struct _s_stack));
        s->elems = malloc(sizeof(stack_elem));
        s->elems[0] = e;
        s->size = 1;
        s->capacity = 1;
    }
    else if (s->size == s->capacity)
    {
        s->capacity = s->capacity * 2;
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
        s->elems[s->size] = e;
        s->size = s->size + 1;
    }
    else
    {
        s->elems[s->size] = e;
        s->size = s->size + 1;
    }
    return s;
}

stack stack_pop(stack s)
{
    assert(!stack_is_empty(s));
    s->size = s->size - 1;
    if (s->size == 0)
    {
        free(s->elems);
        free(s);
        s = NULL;
    }
    return s;
}

unsigned int stack_size(stack s)
{
    return s->size;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s)
{
    return (s == NULL);
}

stack stack_destroy(stack s){
    if(s != NULL){
        free(s->elems);
        free(s);
        s = NULL;
    }
    return s;
}