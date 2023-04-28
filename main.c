#include "shell.h"
#include <stdio.h>

/**
 * main - mian function  of the program
 * @argc: counts  values received from the command line
 * @argv: agument function  received from the command line
 * @env: number of values received from the command line
 * Return: success if zero.
 */
int main(int argc, char *argv[], char *env[])
{
	data_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_TM;
	}
	errno = 0;
	teamwk(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_TM);
}

/**
 * inicialize_data - inicialize the struct with the info of the program
 * @string: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void inicialize_data(data_program *data, int argc, char *argv[], char **env)
{
	int n = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->comand_name = NULL;
	data->exec_counter = 0;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[n]; n++)
		{
			data->env[n] = str_duplicate(env[n]);
		}
	}
	data->env[n] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (n = 0; n < 20; n++)
	{
		data->alias_list[n] = NULL;
	}
}
/**
 * teamwk - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void teamwk(char *prompt, data_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			current_data_free(data);
		}
	}
}
