#include "shell.h"

/**
 * current_data_free - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void current_data_free(data__program *data)
{
	if (data->tokens)
	pointers_of_array_free(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->comand_name)
		free(data->comand_name);

	data->input_line = NULL;
	data->comand_name = NULL;
	data->tokens = NULL;
}

/**
 * data_to_free - free place of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void data_to_free(data_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	current_data_free(data);
	pointers_of_array_free(data->env);
	pointers_of_array_free(data->alias_list);
}

/**
 * pointers_of_array_free - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void pointers_of_array_free(char **array)
{
	int n;

	if (array != NULL)
	{
		for (n = 0; array[n]; n++)
			free(array[n]);

		free(array);
		array = NULL;
	}
}
