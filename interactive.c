#include "shell.h"

/**
 * interactive - function that checks if shell is interactive 
 * @intel: the struct address containing arguments
 *
 * Return: 1 if shell is interactive, 0 if not
 */
int interactive(data *intel)
{
	return (isatty(STDIN_FILENO) && intel->readfd <= 2);
}

/**
 * is_delimeter - function that checks if char is a delimeter
 * @c: character to check
 * @dl: this is the delimeter string
 *
 * Return: 1 if @c is a delimeter, 0 if not
 */

int is_delimeter(char c, char *dl)
{
	while (*dl)
	{
		if (*dl++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - function that looks for alphabetic characters
 * @c: character to be checked
 *
 * Return: 1 if @c is alphabetic,0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - function that converts a string to an integer
 * @x: string to be converted
 * Return: 0 if number is string else converted number
 */

int _atoi(char *x)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  x[i] != '\0' && flag != 2; i++)
	{
		if (x[i] == '-')
			sign *= -1;

		if (x[i] >= '0' && x[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (x[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
