#include "shell.h"
#include <stdio.h>

/**
 * builtin_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exit(data_program *data)
{
	int k;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (k = 0; data->tokens[1][k]; k++)
			if ((data->tokens[1][k] < '0' || data->tokens[1][k] > '9')
				&& data->tokens[1][k] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_cd(data_program *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_work_directory(data_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_help(data_program *data)
{
	int k, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_TM;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->comand_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_TM;
	mensajes[2] = HELP_ENV_TM;
	mensajes[3] = HELP_SETENV_TM;
	mensajes[4] = HELP_UNSETENV_TM;
	mensajes[5] = HELP_CD_TM;

	for (k = 0; mensajes[k]; k++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[k], length))
		{
			_print(mensajes[k] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->comand_name);
	return (0);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_alias(data_program *data)
{
	int k = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++k])
	{/* if there are arguments, set or print each env variable*/
		if (count_characters(data->tokens[k], "="))
			set_alias(data->tokens[k], data);
		else
			print_alias(data, data->tokens[k]);
	}

	return (0);
}
