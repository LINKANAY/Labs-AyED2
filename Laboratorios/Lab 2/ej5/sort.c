#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
       unsigned int i, j , pivot;
       pivot = izq;
       i = izq + 1;
       j = der;
       while (i <= j)
       {
            if (goes_before(a[i], a[pivot]))
            {
                i++;
            }else if (goes_before(a[pivot], a[j]))
            {
                j--;
            }else{
                swap(a, i, j);
                i++;
                j--;
            }        
       }   
       swap(a, pivot, j);
       pivot = j;
       return pivot;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
    unsigned int pivot = izq;
    if (der > izq)
    {
        pivot = partition(a, izq, der);
        quick_sort_rec(a, izq, (pivot));
        quick_sort_rec(a, (pivot+1), der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


static unsigned int partition2(fixstring a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
       unsigned int i, j , pivot;
       pivot = izq;
       i = izq + 1;
       j = der;
       while (i <= j)
       {
            if(fstring_length(a[i]) <= fstring_length(a[pivot]))
            {
                i++;
            }else if (fstring_length(a[j]) > fstring_length(a[pivot]))
            {
                j--;
            }else{
                swap(a, i, j);
                i++;
                j--;
            }        
       }   
       swap(a, pivot, j);
       pivot = j;
       return pivot;
}
static void quick_sort_rec2(fixstring a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
    unsigned int pivot = izq;
    pivot = partition2(a, izq, der);
    
    if (izq < pivot)
    {
        quick_sort_rec2(a, izq, (pivot-1));
    }
    if (pivot < der)
    {
        quick_sort_rec2(a, (pivot+1), der);
    }
}

void quick_sort2(fixstring a[], unsigned int length) {
    quick_sort_rec2(a, 0, (length == 0) ? 0 : length - 1);
}