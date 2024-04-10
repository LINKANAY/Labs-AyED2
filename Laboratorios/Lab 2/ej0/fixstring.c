#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }
    return length;   
}

bool fstring_eq(fixstring s1, fixstring s2) {
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

