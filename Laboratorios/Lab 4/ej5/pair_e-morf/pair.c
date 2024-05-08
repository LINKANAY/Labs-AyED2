#include <stdlib.h> /* EXIT_SUCCESS... */
#include <stdio.h>  /* printf()...     */
#include "pair.h"   /* TAD Par         */

struct s_pair_t
{
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y)
{
    pair_t new;
    new = malloc(sizeof(pair_t));
    new->fst = x;
    new->snd = y;
    return new;
}

int pair_first(pair_t p)
{
    return p->fst;
}

int pair_second(pair_t p)
{
    return p->snd;
}

pair_t pair_swapped(pair_t p)
{
    elem aux;
    aux = 0;
    aux = p->fst;
    p->fst = p->snd;
    p->snd = aux;
    return p;
}

pair_t pair_destroy(pair_t p)
{
    if (p != NULL)
    {
        free(p);
        p = NULL;
    }

    return p;
}
