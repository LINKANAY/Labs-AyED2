/*
Para compilar un archivo .c escribir en la terminal:
$> gcc -Wall -Wextra -std=c99 asoc.c -o picachuYoTeElijo
Para ejecutar escribir:
$> ./miprograma
Para compilar para gdb se debe agregar el flag -g al momento de compilar .c escribir en la
terminal:
$> gcc -Wall -Wextra -std=c99 -g miarchivo.c -o miprograma
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_upperbound = false;
    res.is_lowerbound = false;
    res.exists = false;
    res.where = false;
    for (unsigned int  i = 0; i < length; i++)
    {
        if (value == arr[i])
        {
            res.exists = true;
            res.where = i;
        }

        if (value > arr[i] || value == arr[i])
        {
            res.is_upperbound = true;
        }

        else if (value < arr[i] || value == arr[i])
        {
            res.is_lowerbound = true;
        }        
    }
    
    
    //
    // TODO: COMPLETAR
    //
    return res;
}

int main(void) {
    int a[ARRAY_SIZE] = {0, -1, 9, 4};
    int value=9;
    //
    // TODO: COMPLETAR - Pedir entrada al usuario
    //
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    printf("%d", result.is_upperbound); // Imprime 1
    printf("%d", result.is_lowerbound); // Imprime 0
    printf("%u", result.exists);        // Imprime 1
    printf("%u", result.where);         // Imprime 2

    return EXIT_SUCCESS;
}

