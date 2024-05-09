#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    //
    // Completar aquí
    //
    if (x >= 0)
    {
        y = &x;
    }
    else
    {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---

    //
    // Completar aquí
    //
    a = -10;
    absolute(a, &res);
    printf("abs: %d\n", res);

    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}
//es de tipo out