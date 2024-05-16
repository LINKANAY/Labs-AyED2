#ifndef STRFUNCS_H
#define STRFUNCS_H

#include <stdbool.h>
#include <stddef.h>


size_t string_length(const char *str);
char *string_filter(const char *str, char c);
bool string_is_symmetric(const char *str);

#endif