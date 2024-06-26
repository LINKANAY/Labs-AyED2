#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot = izq;
    if (der > izq)
    {
        pivot = partition(a, izq, der);
        quick_sort_rec(a, izq, (pivot));
        quick_sort_rec(a, (pivot+1), der);
    }
    


 /* needs implementation */

    /* no implementes partition, ya está implementado en sort_helpers.o
       (no se puede leer, pero en sort_helpers.h vas a encontrar información
        para saber cómo usarlo)
    */
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}


