#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y)
{
    //
    // Completar aquí
    //
    if (x >= 0)
    {
        y = x;
    }
    else
    {
        y = x*(-1);
    }
}

int main(void)
{
    int a = 0, res = 0;
    //
    // Completar aquí
    //
    a = -10;
    absolute(a, res);
    printf("abs: %d\n", res);
    return EXIT_SUCCESS;
}

//no coincide con el teorico/practico