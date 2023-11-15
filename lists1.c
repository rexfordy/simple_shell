#include "shell.h"

/**
 * list_len - This determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * list_to_strings - This returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t e = list_len(head), f;
	char **strs;
	char *str;

	if (!head || !e)
		return (NULL);
	strs = malloc(sizeof(char *) * (e + 1));
	if (!strs)
		return (NULL);
	for (e = 0; node; node = node->next, e++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (f = 0; f < e; f++)
				free(strs[f]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[e] = str;
	}
	strs[e] = NULL;
	return (strs);
}


/**
 * print_list - This prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * node_starts_with - This returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t e = 0;

	while (head)
	{
		if (head == node)
			return (e);
		head = head->next;
		e++;
	}
	return (-1);
}
