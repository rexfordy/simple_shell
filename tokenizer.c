#include "shell.h"

/**
 * **strtow - This splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int e, f, g, l, numwords = 0;
	char **y;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (e = 0; str[e] != '\0'; e++)
		if (!is_delim(str[e], d) && (is_delim(str[e + 1], d) || !str[e + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	y = malloc((1 + numwords) * sizeof(char *));
	if (!y)
		return (NULL);
	for (e = 0, f = 0; f < numwords; f++)
	{
		while (is_delim(str[e], d))
			e++;
		g = 0;
		while (!is_delim(str[e + g], d) && str[e + g])
			g++;
		y[f] = malloc((g + 1) * sizeof(char));
		if (!y[f])
		{
			for (g = 0; g < f; g++)
				free(y[g]);
			free(y);
			return (NULL);
		}
		for (l = 0; l < g; l++)
			y[f][l] = str[e++];
		y[f][l] = 0;
	}
	y[f] = NULL;
	return (y);
}

/**
 * **strtow2 - This splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int e, f, g, l, numwords = 0;
	char **y;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != d && str[e + 1] == d) ||
		 (str[e] != d && !str[e + 1]) || str[e + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	y = malloc((1 + numwords) * sizeof(char *));
	if (!y)
		return (NULL);
	for (e = 0, f = 0; f < numwords; f++)
	{
		while (str[e] == d && str[e] != d)
			e++;
		g = 0;
		while (str[e + g] != d && str[e + g] && str[e + g] != d)
			g++;
		y[f] = malloc((g + 1) * sizeof(char));
		if (!y[f])
		{
			for (g = 0; g < f; g++)
				free(y[g]);
			free(y);
			return (NULL);
		}
		for (l = 0; l < g; l++)
			y[f][l] = str[e++];
		y[f][l] = 0;
	}
	y[f] = NULL;
	return (y);
}
