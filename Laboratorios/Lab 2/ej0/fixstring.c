#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int longitud = 0;
    for (unsigned int i = 0; i < FIXSTRING_MAX; i++)
    {
        if (s[i] != 0)
        {
            longitud++;
        }
        else{
            break;
        }
    }
    return longitud;   
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool iguales = true;
    for (unsigned int i = 0; i < FIXSTRING_MAX; i++)
    {
        if (s1[i] != s2[i] || (s1[i] == ' ' && s2[i] == ' '))
        {
            iguales = false;
            break;
        }
    }
    return iguales;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool menorIgual = true;
    for (unsigned int i = 0; i < FIXSTRING_MAX; i++)
    {
        if (s1[i] > s2[i])
        {
            menorIgual = false;
            break;
        }
    }
    return menorIgual;
}

