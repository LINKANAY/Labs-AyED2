#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

char *string_filter(const char *str, char c)
{
    size_t len = string_length(str);
    size_t count = 0;

    // cantidad de caracteres distintos de 'c'
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != c)
        {
            count++;
        }
    }

    // asigno memoria para la nueva cadena
    char *filtered_str = (char *)malloc((count + 1) * sizeof(char));
    if (filtered_str == NULL)
    {
        return NULL;
    }

    // guardo los caracteres distintos de 'c'
    size_t j = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] != c)
        {
            filtered_str[j] = str[i];
            j++;
        }
    }
    filtered_str[j] = '\0'; // agrego el caracter nulo

    return filtered_str;
}

bool string_is_symmetric(const char *str)
{
    size_t len = string_length(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - i - 1])
        {
            return false;
        }
    }
    return true;
}
