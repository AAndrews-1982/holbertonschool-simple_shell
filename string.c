#include "shell.h"

/**
 * _strdup - Duplicates a string by creating a new string in memory
 *           and copying the contents of the given string.
 * @str: The string to be duplicated.
 *
 * Return: A pointer to the newly allocated duplicated string, or NULL if
 *         memory allocation fails or the input string is NULL.
 */

char *_strdup(char *str)
{
	int i;
	char *dest_str = NULL;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		;
	dest_str = malloc(sizeof(char) * (i + 1));
	if (dest_str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		dest_str[i] = str[i];
	}
	dest_str[i] = '\0';
	return (dest_str);
}

/**
 * _strcpy - copies a string to a buffer
 * @dest: buffer to copy to
 * @src: string to copy
 *
 * Return: pointer to the resulting string
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strlen - computes the length of a string
 * @s: string to compute the length of
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;

	return (i);
}

/**
 * _strncmp - compares n characters of two strings
 * @s1: first string to compare
 * @s2: second string to compare
 * @n: number of characters to compare
 *
 * Return: difference between the first non-matching characters
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; i < n && s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	return (0);
}
