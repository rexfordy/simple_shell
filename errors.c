#include "shell.h"

/**
 *_eputs - This prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - This writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putfd - This writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 *_putsfd - This prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}
