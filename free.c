#include "shell.h"

/**
 * befree - function that frees a pointer and NULLs the address to that pointer
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, Otherwise 0
 */

int befree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
