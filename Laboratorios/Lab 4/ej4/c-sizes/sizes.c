#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void print_data(data_t d)
{
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void)
{

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n",
           /* COMPLETAR */
           sizeof(messi.name), sizeof(messi.age), sizeof(messi.height),
           sizeof(data_t));

    /*
     *
     * COMPLETAR
     *
     */
    printf("name-indice  : %lu\n"
           "age-indice   : %lu\n"
           "height-indice: %lu\n"
           "data_t-indice: %lu\n",
           /* COMPLETAR */ 
           (uintptr_t)messi.name, (uintptr_t)messi.age,
           (uintptr_t)messi.height, (uintptr_t)&messi);

    printf("name-address   : %p\n"
           "age-address    : %p\n"
           "height-address : %p\n"
           "data_t-address : %p\n",
           /* COMPLETAR */ 
           (void *)&messi.name, (void *)&messi.age,
           (void *)&messi.height, (void *)&messi);

    return EXIT_SUCCESS;
}
// ¿La suma de los miembros coincide con el total? --> NO

// ¿El tamaño del campo name depende del nombre que contiene? --> NO

// ¿Hay algo raro en las direcciones de memoria? --> Si, los indices y
// direcciones del nombre y de la estructura son iguales