#include "shell.h"

/**
 * _history - function that displays history 
 * @intel: shell structure containing potential arguments.
 *
 *  Return: Always 0, success
 */

int _history(data *intel)
{
	print_list(intel->history);
	return (0);
}

/**
 * unset_alias - function that unsets alias to string
 * @intel: this is a parameter struct containing arguments
 * @str: is the string alias to check
 *
 * Return: Always 0 on success, 1 Error
 */

int unset_alias(data *intel, char *str)
{
	char *q, d;
	int re;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	re = delete_node_at_index(&(intel->alias),
		get_node_index(intel->alias, node_starts_with(intel->alias, str, -1)));
	*q = d;
	return (re);
}

/**
 * set_alias - function that sets alias to string
 * @intel: this is the parameter struct having arguments
 * @str1: this is the string alias to set
 *
 * Return: Always 0 on success, 1 Error
 */

int set_alias(data *intel, char *str1)
{
	char *q;

	q = _strchr(str1, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(intel, str1));

	unset_alias(intel, str1);
	return (add_node_end(&(intel->alias), str1, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @node1: is the alias node
 *
 * Return: Always 0 on success, 1 Error
 */

int print_alias(list_t *node1)
{
	char *q = NULL, *a = NULL;

	if (node1)
	{
		q = _strchr(node1->str, '=');
		for (a = node1->str; a <= q; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - function that copies the alias in builtin
 * @intel: Structure that has potential arguments, and
 * constant function prototype.
 *
 *  Return: Always 0
 */

int _alias(data *intel)
{
	int j = 0;
	char *q = NULL;
	list_t *node2 = NULL;

	if (intel->argc == 1)
	{
		node2 = intel->alias;
		while (node2)
		{
			print_alias(node2);
			node2 = node2->next;
		}
		return (0);
	}
	for (j = 1; intel->argv[j]; j++)
	{
		q = _strchr(intel->argv[j], '=');
		if (q)
			set_alias(intel, intel->argv[j]);
		else
			print_alias(node_starts_with(intel->alias, intel->argv[j], '='));
	}

	return (0);
}
