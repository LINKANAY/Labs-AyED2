
#include <stdlib.h>
#include <stdio.h>

#include "funtion.h"

void dump(char a[], unsigned int length)
{
    printf("\"");
    for (unsigned int j = 0u; j < length; j++)
    {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size)
{
    FILE *file = NULL;
    file = fopen(path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Fie does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int length = 0;
    int i = 0;
    while (feof(file) == 0 && length < max_size)
    {
        fscanf(file, "%u -> *%c*", &indexes[i], &letters[i]);
        length++;
        i++;
    }
    length--;

    fclose(file);
    return length;
}

void arraySorted(unsigned int indexes[], char letters[], char sorterd[], unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
    {
        for (unsigned int j = 0; j < length; j++)
        {
            if (i == indexes[j])
            {
                sorterd[i] = letters[j];
            }            
        }
    }
}

char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    if (argc < 2)
    {
        // print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    result = argv[1];
    return result;
}
