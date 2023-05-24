#include "shell.h"

/**
 * get_history_file - function that gets the shell history file
 * @info: is parameter struct that contains arguments
 *
 * Return: allocated string containing shell history file
 */

char *get_history_file(data *intel)
{
	char *buff, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - function that creates a file, or appends existing files
 * @info: is the parameter struct containing arguments
 *
 * Return: 1 on success,
 *	otherwise -1
 */
int write_history(data *intel)
{
	ssize_t fd;
	char *filenm = get_history_file(intel);
	list_t *node = NULL;

	if (!filenm)
		return (-1);

	fd = open(filenm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenm);
	if (fd == -1)
		return (-1);
	for (node = intel->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - function that reads history from existing shell files
 * @intel:is the parameter struct containing arguments
 *
 * Return: history count on success,
 *	0 on failure
 */

int read_history(data *intel)
{
	int j, last = 0, linecount = 0;
	ssize_t d, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filenam = get_history_file(intel);

	if (!filenam)
		return (0);

	d = open(filenam, O_RDONLY);
	free(filenam);
	if (d == -1)
		return (0);
	if (!fstat(d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(d, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(d);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(intel, buf + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(intel, buf + last, linecount++);
	free(buf);
	intel->histcount = linecount;
	while (intel->histcount-- >= HIST_MAX)
		delete_node_at_index(&(intel->history), 0);
	renumber_history(intel);
	return (intel->histcount);
}

/**
 * build_history_list - function that adds entry to history linked list
 * @intel: Structure that has possible arguments
 * @buff: buffer memory
 * @linecount1: history linecount
 *
 * Return: Always 0
 */

int build_history_list(data *intel, char *buff, int linecount1)
{
	list_t *node = NULL;

	if (intel->history)
		node = intel->history;
	add_node_end(&node, buff, linecount1);

	if (!intel->history)
		intel->history = node;
	return (0);
}

/**
 * renumber_history - function that renumbers history after changes to history
 * @intel: Structure that has arguments
 *
 * Return: the new history count
 */

int renumber_history(data *intel)
{
	list_t *node = intel->history;
	int y = 0;

	while (node)
	{
		node->num = y++;
		node = node->next;
	}
	return (intel->histcount = y);
}
