#include "shell.h"

/**
 * _env - function that prints the current shell environment
 * @intel: Structure that has potential arguments.
 *
 * Return: Always 0
 */

int _env(data *intel)
{
	print_list_str(intel->env);
	return (0);
}

/**
 * _getenv - function that gets the value of an environment variable
 * @intel: Structure tht has possible arguments
 * @nm: environent variable name
 *
 * Return: env variable value
 */

char *_getenv(data *intel, const char *nm)
{
	list_t *node1 = i->env;
	char *q;

	while (node1)
	{
		q = starts_with(node1->str, nm);
		if (q && *q)
			return (q);
		node1 = node1->next;
	}
	return (NULL);
}

/**
 * _setenv - function that Initialize  new environment variable,
 * or modify existing ones
 * @intel: Structure that has arguments
 *
 *  Return: Always 0
 */

int _setenv(data *intel)
{
	if (intel->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(intel, intel->argv[1], intel->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - function that Removes an environment variable
 * @intel: Structure containing potential arguments.
 *
 *  Return: Always 0
 */

int _unsetenv(data *intel)
{
	int y;

	if (intel->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (y = 1; y <= intel->argc; y++)
		_unsetenv(intel, intel->argv[y]);

	return (0);
}

/**
 * populate_env_list -function that populates environmnt linked list
 * @intel: Structure that has  arguments
 *
 * Return: Always 0
 */

int populate_env_list(data *intel)
{
	list_t *node = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		add_node_end(&node, environ[y], 0);
	intel->env = node;
	return (0);
}
