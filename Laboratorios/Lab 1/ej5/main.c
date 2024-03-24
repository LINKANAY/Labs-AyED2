/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "mybool.h"

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    mybool ordenado = false;
    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /*dumping the array*/
    array_dump(array, length);
    ordenado = array_is_sorted(array, length);
    if (ordenado)
    {
        printf("El arreglo está ordenado.\n");
    }else{
        printf("El arreglo no está ordenado.\n");
    }
    
    return EXIT_SUCCESS;
}
