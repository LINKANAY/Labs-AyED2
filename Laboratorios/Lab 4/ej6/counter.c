#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"

struct _counter
{
    unsigned int count;
};

counter counter_init(void)
{
    counter new = NULL;
    new = malloc(sizeof(struct _counter));
    new->count = 0;
    return new;
}

void counter_inc(counter c)
{
    c->count += 1;
}

bool counter_is_init(counter c)
{
    return (c != NULL);
}

void counter_dec(counter c)
{
    if (counter_is_init(c))
    {
        c->count -= 1;
    }
}

counter counter_copy(counter c)
{
    counter copy = NULL;
    copy = malloc(sizeof(struct _counter));
    if (copy == NULL)
    {
        return NULL;
    }
    copy->count = c->count;
    return copy;
}

void counter_destroy(counter c)
{
    if (c != NULL)
    {
        free(c);
        c = NULL;
    }
}
