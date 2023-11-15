#include "shell.h"

/**
 * interactive - This returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - This checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - This converts a string to an integer
 *@y: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *y)
{
	int e, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (e = 0; y[e] != '\0' && flag != 2; e++)
	{
		if (y[e] == '-')
			sign *= -1;

		if (y[e] >= '0' && y[e] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (y[e] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


