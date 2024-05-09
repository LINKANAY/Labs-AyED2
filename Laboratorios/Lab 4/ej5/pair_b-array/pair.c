#include <stdlib.h> /* EXIT_SUCCESS... */
#include <stdio.h>  /* printf()...     */
#include "pair.h"   /* TAD Par         */

pair_t pair_new(int x, int y)
{
    pair_t new;
    for (unsigned i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            new.values[i] = x;
        }
        else if (i == 1)
        {
            new.values[i] = y;
        }
    }
    return new;
}

int pair_first(pair_t p)
{
    return p.values[0];
}

int pair_second(pair_t p)
{
    return p.values[1];
}

pair_t pair_swapped(pair_t p)
{
    int aux;
    aux = p.values[1];
    p.values[1] = p.values[0];
    p.values[0] = aux;
    return p;
}

pair_t pair_destroy(pair_t p)
{
    p.values[0] = 0;
    p.values[1] = 0;
    return p;
}
