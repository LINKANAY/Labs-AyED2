#include <array_helpers.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return 0;
    }

    unsigned int dimension;
    if (fscanf(file, "%u", &dimension) != 1) {
        printf("Error: No se pudo leer la dimensión del arreglo.\n");
        fclose(file);
        return 0;
    }

    if (dimension < max_size)
    {
         for (unsigned int i = 0; i < dimension; i++)
        {
            fscanf(file, "%d", &array[i]);
        }
    }
    
    
    
    fclose(file);
    return dimension;
    
}

void array_dump(int a[], unsigned int length) {
    printf("dimension del arreglo: %u\n", length);
    printf("[");
    for (unsigned int i = 0; i < length; i++) {
        printf(" %d", a[i]);
        if (i < length - 1) {
            printf(",");
        }
    }
    printf(" ]\n");
}