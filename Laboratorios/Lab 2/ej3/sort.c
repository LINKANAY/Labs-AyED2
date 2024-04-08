#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    /* Needs implementation */

    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */
   unsigned int leftT, rightT, pivot;
    pivot = izq;
    leftT = izq +1;
    rightT = der;
    while (leftT <= rightT)
    {
        while (leftT < der && goes_before(a[leftT], a[pivot]))
        {
            leftT++;
        }
        while (rightT > izq && goes_before(a[pivot], a[rightT]))
        {
            rightT--;
        }
        if (leftT < rightT)
        {
            swap(a, leftT, rightT);
            leftT++;
            rightT--;
        }
    }
    swap(a, pivot, rightT);
    pivot = rightT;
    return pivot;
}

void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot = izq;
    printf("uno %u, %u, %u\n", izq, pivot, der);
    array_dump(a, pivot);
    if (der > izq)
    {
        pivot = partition(a, izq, der);
        printf("dos %u, %u, %u\n", izq, pivot, der);
        array_dump(a, pivot);
        quick_sort_rec(a, izq, (pivot));
        printf("tres %u, %u, %u\n", izq, pivot, der);
        array_dump(a, pivot);
        quick_sort_rec(a, (pivot), der);
    }
    


 /* needs implementation */

    /* no implementes partition, ya está implementado en sort_helpers.o
       (no se puede leer, pero en sort_helpers.h vas a encontrar información
        para saber cómo usarlo)
    */
}


void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

