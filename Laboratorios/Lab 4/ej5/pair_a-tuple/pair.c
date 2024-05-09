#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

pair_t pair_new(int x, int y){
    pair_t new;
    new.fst = x;
    new.snd = y;
    return new;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t temp;
    temp = p;
    int aux;
    aux = temp.fst;
    temp.fst = temp.snd;
    temp.snd = aux;
    return temp;
}

pair_t pair_destroy(pair_t p){
     p.fst = 0;
     p.snd = 0;
     return p;
}