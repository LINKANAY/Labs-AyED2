#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int longitud = 0;

    stack st = stack_empty();
    st = stack_push(st, 1);
    st = stack_push(st, 2);
    st = stack_push(st, 3);
    printf("elems: %d\n", stack_size(st));
    stack_elem *lista = stack_to_array(st);
    for (unsigned int i = 0; i < stack_size(st); i++)
    {
        printf("elem %d: %d\n", i, lista[i]);
    }
    // stack_destroy(st);
    return EXIT_SUCCESS;
}

// ¿Funciona bien stack_pop() para pilas de tamaño 1?
//  Rta: si funciona

// Si la pila queda vacía, ¿puedo volver a insertar elementos?
// Rta: si se puede agregar elementos.

// ¿La función stack_to_array() devuelve NULL para una pila vacía? ¿Devuelve los
//  elementos en el orden correcto?