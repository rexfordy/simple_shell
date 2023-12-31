#include "shell.h"

/**
 * is_chain - This tests if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t f = *p;

	if (buf[f] == '|' && buf[f + 1] == '|')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[f] == '&' && buf[f + 1] == '&')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[f] == ';') /* found end of this command */
	{
		buf[f] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = f;
	return (1);
}

/**
 * check_chain - This checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @e: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t e, size_t len)
{
	size_t f = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[e] = 0;
			f = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[e] = 0;
			f = len;
		}
	}

	*p = f;
}

/**
 * replace_alias - This replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int e;
	list_t *node;
	char *p;

	for (e = 0; e < 10; e++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - This replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[e][1], '=');
		if (node)
		{
			replace_string(&(info->argv[e]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[e], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - This replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
