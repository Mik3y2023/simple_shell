#include "shell.h"

/**
 * _exit - this is where the main exits function
 * @intel: Structure that has possible arguments.
 *
 *  Return: exits with  exit status
 *         (0) when info.argv[0] != "exit"
 */

int _exit(data *intel)
{
	int exit_checker;

	if (intel->argv[1]) 
	{
		exit_checker = _erratoi(intel->argv[1]);
		if (exit_checker == -1)
		{
			intel->status = 2;
			print_error(intel, "Invalid: ");
			_eputs(intel->argv[1]);
			_eputchar('\n');
			return (1);
		}
		intel->err_num = _erratoi(intel->argv[1]);
		return (-2);
	}
	intel->err_num = -1;
	return (-2);
}

/**
 * _cd - function that changes current directory in shell,
 * using the cd command prompt
 * @intel: Structure that contains has possible arguments.
 *
 *  Return: Always 0, success
 */

int _cd(data *intel)
{
	char *z, *dr, buffer[1024];
	int chdir_ret;

	z = getcwd(buffer, 1024);
	if (!z)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!intel->argv[1])
	{
		dr = _getenv(intel, "HOME=");
		if (!dr)
			chdir_ret = /*  return change directory */
				chdir((dr = _getenv(intel, "PWD=")) ? dr : "/");
		else
			chdir_ret = chdir(dr);
	}
	else if (_strcmp(intel->argv[1], "-") == 0)
	{
		if (!_getenv(intel, "OLDPWD="))
		{
			_puts(z);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(intel, "OLDPWD=")), _putchar('\n');
		chdir_ret = /*  return change directory */
			chdir((dr = _getenv(intel, "OLDPWD=")) ? dr : "/");
	}
	else
		chdir_ret = chdir(intel->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(intel, "can't cd to ");
		_eputs(intel->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(intel, "OLDPWD", _getenv(intel, "PWD="));
		_setenv(intel, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - function that lists help menus
 * @intel: Structure tht has potential arguments, maintains
 * constant function prototype.
 *
 *  Return: Always 0
 */
int _help(data *intel)
{
	char **arg_arr;

	arg_arr = intel->argv;
	_puts(" Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); 
	return (0);
}
