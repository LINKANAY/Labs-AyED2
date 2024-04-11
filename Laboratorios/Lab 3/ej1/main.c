#include <stdlib.h>
#include <stdio.h>

#include "funtion.h"
#define MAX_SIZE 1000


int main(int argc, char *argv[]) {
    //FILE *file;
    char *filepath = NULL;
    filepath = parse_filepath(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length= data_from_file(filepath, indexes, letters, MAX_SIZE); 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    /* -- completar -- */
    dump(letters, length);
    arraySorted(indexes, letters, sorted, length);
    dump(sorted, length);

    return EXIT_SUCCESS;
}
