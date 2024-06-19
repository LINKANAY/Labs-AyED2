#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

int main ()
{
    string str1 = string_create("hola");
    string str2 = string_create("hola");
    bool menor = string_less(str1, str2);
    bool igual = string_eq(str1, str2);
    printf("Menor: %d\n", menor);
    printf("Igual: %d\n", igual);
    string_destroy(str1);
    string_destroy(str2);
    
}