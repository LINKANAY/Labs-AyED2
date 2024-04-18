/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    // completar aquí
    return x.rank <= y.rank;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void sort(player_t a[], unsigned int length) {
    // completar aquí
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length -1u);
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
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

void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 2 */
    //unsigned int pivot = izq;
    if (der > izq)
    {
        unsigned int pivot = partition(a, izq, der);
        quick_sort_rec(a, izq, (pivot == 0u) ? 0u : pivot -1u);
        quick_sort_rec(a, (pivot+1), der);
    }
}

void swap(player_t a[], unsigned int i, unsigned int j){
    player_t tempo;
    tempo = a[i];
    a[i] = a[j];
    a[j] = tempo;
}