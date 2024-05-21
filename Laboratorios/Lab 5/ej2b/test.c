#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // unsigned int longitud = 0;

    stack st = stack_empty();
    st = stack_push(st, 1);
    st = stack_push(st, 2);
    st = stack_push(st, 3);
    printf("longitud: %d\n", stack_size(st));
    stack_elem *lista = NULL;
    lista = stack_to_array(st);
    unsigned int longLista = stack_size(st);
    for (unsigned int i = 0; i < longLista; i++)
    {
        printf("elemento de lista %d: %d\n", i, lista[i]);
    }
    stack_destroy(st);
    free(lista);
    lista = NULL;
    return EXIT_SUCCESS;
}

// ¿Funciona bien stack_pop() para pilas de tamaño 1?
//  Rta: si funciona

// Si la pila queda vacía, ¿puedo volver a insertar elementos?
// Rta: si se puede agregar elementos.

// ¿La función stack_to_array() devuelve NULL para una pila vacía? 
//Rta: no devuelve null
//¿Devuelve los elementos en el orden correcto?
//Rta: si devuelve los elementos en el orden correcto