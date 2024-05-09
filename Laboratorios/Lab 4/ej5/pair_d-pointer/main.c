#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", pair_first(p), pair_second(p));
}

int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    // Se muestra el par por pantalla
    printf("x %d\n", pair_first(p));
    printf("y %d\n", pair_second(p));
    printf("direccion p %p\n", (void *)p);
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // Se muestra q
    printf("x %d\n", pair_first(q));
    printf("y %d\n", pair_second(q));
    printf("direccion q %p\n", (void *)q);
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    printf("valor p %p\n", (void *)p);
    q = pair_destroy(q);
    printf("valor q %p\n", (void *)q);
    
    return EXIT_SUCCESS;
}
