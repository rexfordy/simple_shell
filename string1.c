#include "shell.h"

/**
 * _strcpy - This  copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int e = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[e])
	{
		dest[e] = src[e];
		e++;
	}
	dest[e] = 0;
	return (dest);
}

/**
 * _strdup - This duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - This prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_putchar(str[e]);
		e++;
	}
}

/**
 * _putchar - This writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}
