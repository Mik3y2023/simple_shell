#include "shell.h"

/**
 * get_environ - function that returns the string array copy,
 * of the shell environment
 * @intel: Structure that has potential arguments.
 *
 * Return: Always 0
 */

char **get_environ(data *intel)
{
	if (!intel->environ || intel->env_changed)
	{
		intel->environ = list_to_strings(intel->env);
		intel->env_changed = 0;
	}

	return (intel->environ);
}

/**
 * _unsetenv - function that unsets environment variables
 * @intel: Structure that has arguments
 * @vari: the string environment variable property
 *
 *  Return: 1 for unset var
 *	0 otherwise
 *
 */
int _unsetenv(data *intel, char *vari)
{
	list_t *node = intel->env;
	size_t y = 0;
	char *c;

	if (!node || !vari)
		return (0);

	while (node)
	{
		c = starts_with(node->str, vari);
		if (c && *c == '=')
		{
			intel->env_changed = delete_node_at_index(&(intel->env), y);
			y = 0;
			node = intel->env;
			continue;
		}
		node = node->next;
		y++;
	}
	return (intel->env_changed);
}

/**
 * _setenv - function that Initialize a new environment variable,
 * or modify an existing one
 * @intel: Structure that has arguments
 * @var:  string environent variable to initialize
 * @value:  string environment variable value to be initialized
 *
 *  Return: Always 0
 */
int _setenv(data *intel, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *c;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = intel->env;
	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buff;
			intel->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(intel->env), buff, 0);
	free(buff);
	intel->env_changed = 1;
	return (0);
}
