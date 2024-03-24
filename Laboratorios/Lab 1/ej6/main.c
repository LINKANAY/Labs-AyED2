/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include <stdbool.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    bool ordenado = false;
    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    unsigned int inicio = 0;
    unsigned int fin = length -1;
    unsigned int temp;
    while (inicio < fin)
    {
        temp = array[inicio];
        array[inicio] = array[fin];
        array[fin] = temp;

        inicio++;
        fin--;
    }

    


    /*dumping the array*/
    array_dump(array, length);
    ordenado = array_is_sorted(array, length);  //ordenado ?
    if (ordenado)
    {
        printf("El arreglo está ordenado.\n");
    }else{
        printf("El arreglo no está ordenado.\n");
    }
    
    return EXIT_SUCCESS;
}
