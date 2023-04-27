#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(data_program *data)
{
	int n, k;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (n = 0; line[n]; n++)
		if (line[n] == '#')
			line[n--] = '\0';
		else if (line[n] == '$' && line[n + 1] == '?')
		{
			line[n] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + n + 2);
		}
		else if (line[n] == '$' && line[n + 1] == '$')
		{
			line[n] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + n + 2);
		}
		else if (line[n] == '$' && (line[n + 1] == ' ' || line[n + 1] == '\0'))
			continue;
		else if (line[n] == '$')
		{
			for (k = 1; line[n + k] && line[n + k] != ' '; k++)
				expansion[k - 1] = line[n + k];
			temp = env_get_key(expansion, data);
			line[n] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + n + k);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_program *data)
{
	int n, k, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (n = 0; line[n]; n++)
	{
		for (k = 0; line[n + k] && line[n + k] != ' '; k++)
			expansion[j] = line[n + k];
		expansion[k] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + n + k);
			line[n] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, n;

	length = str_length(buffer);
	for (n = 0; str_to_add[n]; n++)
	{
		buffer[length + n] = str_to_add[n];
	}
	buffer[length + n] = '\0';
	return (length + n);
}
