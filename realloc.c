#include "shell.h"

/**
 **_memset - This fills memory with a constant byte
 *@y: the pointer to the memory area
 *@b: the byte to fill *y with
 *@n: the amount of bytes to be filled
 *Return: (y) a pointer to the memory area y
 */
char *_memset(char *y, char b, unsigned int n)
{
	unsigned int e;

	for (e = 0; e < n; e++)
		y[e] = b;
	return (y);
}

/**
 * ffree - This frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - This reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
