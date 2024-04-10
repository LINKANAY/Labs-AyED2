#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    /* copiá acá la implementación que hiciste en el ejercicio 0 */
    unsigned int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }
    return length; 
}

bool fstring_eq(fixstring s1, fixstring s2) {
    /* copiá acá la implementación que hiciste en el ejercicio 0 */
    bool same = false;
    if (fstring_length(s1) == fstring_length(s2))
    {
        unsigned int i = 0;
        while (i < fstring_length(s1))
        {
            if (s1[i] == s2[i])
            {
                same = true;
            }
            i++;            
        }        
    }
    return same;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    /* copiá acá la implementación que hiciste en el ejercicio 0 */
    unsigned int lengthS1 = fstring_length(s1);
    unsigned int lengthS2 = fstring_length(s2);    
    unsigned int minLength = (lengthS1 < lengthS2) ? lengthS1 : lengthS2;

    for (unsigned int i = 0; i < minLength; i++)
    {
        if (s1[i] < s2[i])
        {
            return true;
        }else if (s1[i] > s2[i])
        {
            return false;
        }        
    }
    return (lengthS1 <= lengthS2);
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    /*
     * COMPLETAR
     *
     */
    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
}


