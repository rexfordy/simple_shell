#include "shell.h"

/**
 **_strncpy - This copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int e, f;
	char *y = dest;

	e = 0;
	while (src[e] != '\0' && e < n - 1)
	{
		dest[e] = src[e];
		e++;
	}
	if (e < n)
	{
		f = e;
		while (f < n)
		{
			dest[f] = '\0';
			f++;
		}
	}
	return (y);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int e, f;
	char *y = dest;

	e = 0;
	f = 0;
	while (dest[e] != '\0')
		e++;
	while (src[f] != '\0' && f < n)
	{
		dest[e] = src[f];
		e++;
		f++;
	}
	if (f < n)
		dest[e] = '\0';
	return (y);
}

/**
 **_strchr - locates a character in a string
 *@y: the string to be parsed
 *@c: the character to look for
 *Return: (y) a pointer to the memory area y
 */
char *_strchr(char *y, char c)
{
	do {
		if (*y == c)
			return (y);
	} while (*y++ != '\0');

	return (NULL);
}
