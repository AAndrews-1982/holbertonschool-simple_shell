#include "shell.h"
#include <ctype.h>

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: The difference between the two strings.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	/* Iterate through both strings until they match or reach the end */
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		/* If the characters are not equal, return the difference */
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}

	/* If the strings have different lengths, return the difference */
	return (s1[i] - s2[i]);
}
/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string, where the result will be stored.
 * @src: The source string to be appended.
 *
 * Return: A pointer to the destination string.
 */
char *_strcat(char *dest, char *src)
{
	int dest_len, i;

	/* Calculate the length of the destination string */
	for (dest_len = 0; dest[dest_len] != '\0'; dest_len++)
		;

	/* Iterate through the source string and append it to the destination */
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	/* Add the null-terminating character to the destination string */
	dest[dest_len + i] = '\0';

	return (dest);
}
