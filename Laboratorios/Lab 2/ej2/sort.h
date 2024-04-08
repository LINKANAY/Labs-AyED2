#ifndef _SORT_H
#define _SORT_H

#include <stdbool.h>

void quick_sort(int a[], unsigned int length);
/*
    Sort the array 'a' using the Quicksort algorithm. The resulting sort
    will be ascending according to the goes_before funtion.

    The array 'a' must have exactly 'length' elements.

*/
void quick_sort_rec(int a[], unsigned int izq, unsigned int der);

#endif
