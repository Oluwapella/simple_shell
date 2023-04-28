#include "shell.h"
#include <stdio.h>

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(data_program *data, char *alias)
{
	int n, k, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (n = 0; data->alias_list[n]; n++)
		{
			if (!alias || (str_compare(data->alias_list[n], alias, alias_length)
				&&	data->alias_list[n][alias_length] == '='))
			{
				for (k = 0; data->alias_list[n][k]; k++)
				{
					buffer[k] = data->alias_list[n][k];
					if (data->alias_list[n][k] == '=')
						break;
				}
				buffer[k + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[n] + k + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(data_program *data, char *name)
{
	int n, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (n = 0; data->alias_list[n]; n++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_list[n], alias_length) &&
			data->alias_list[n][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[n] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, data_program *data)
{
	int n, k;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (n = 0; alias_string[n]; n++)
		if (alias_string[n] != '=')
			buffer[n] = alias_string[n];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + n + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (k = 0; data->alias_list[k]; k++)
		if (str_compare(buffer, data->alias_list[k], n) &&
			data->alias_list[k][n] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[k]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[k] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[k] = str_duplicate(alias_string);
	return (0);
}
