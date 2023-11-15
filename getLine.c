#include "shell.h"

/**
 * input_buf - This buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - This gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t e, f, len;
	ssize_t x = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		f = e; /* init new iterator to current buf position */
		p = buf + e; /* get pointer for return */

		check_chain(info, buf, &f, e, len);
		while (f < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &f))
				break;
			f++;
		}

		e = f + 1; /* increment past nulled ';'' */
		if (e >= len) /* reached end of buffer? */
		{
			e = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (x); /* return length of buffer from _getline() */
}

/**
 * read_buf - This reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @e: size
 *
 * Return: x
 */
ssize_t read_buf(info_t *info, char *buf, size_t *e)
{
	ssize_t x = 0;

	if (*e)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*e = x;
	return (x);
}

/**
 * _getline - This gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: y
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t e, len;
	size_t g;
	ssize_t x = 0, y = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		y = *length;
	if (e == len)
		e = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = _strchr(buf + e, '\n');
	g = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, y, y ? y + g : g + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (y)
		_strncat(new_p, buf + e, g - e);
	else
		_strncpy(new_p, buf + e, g - e + 1);

	y += g - e;
	e = g;
	p = new_p;

	if (length)
		*length = y;
	*ptr = p;
	return (y);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
