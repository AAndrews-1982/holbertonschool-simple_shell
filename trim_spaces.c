#include "shell.h"
#include <ctype.h>

/**
 * trim_spaces - Removes leading and trailing spaces from a string
 * @str: The string to trim
 *
 * Return: A pointer to the trimmed string
 */
char *trim_spaces(char *str)
{
    char *end;

    /* Trim leading spaces */
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  /* All spaces? */
        return str;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    /* Write new null terminator character */
    end[1] = '\0';

    return str;
}