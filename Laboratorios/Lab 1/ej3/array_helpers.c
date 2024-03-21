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

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}
