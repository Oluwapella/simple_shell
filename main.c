#include "shell.h"
/**
 * main - mian function  of the program
 * @argc: counts  values received from the command line
 * @argv: agument function  received from the command line
 * @env: number of values received from the command line
 * Return: success if zero.
 */
int main(int argc, char *argv[], char *env[])
{
	data_program data_struct = {NULL}, *string = &data_struct;
	char *prompt = "";

	in_data(data, argc, argv, env);

	signal(SIGINT, con_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_TM;
	}
	errno = 0;
	teamwk(prompt, string);
	return (0);
}

/**
 * con_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void con_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_TM);
}

/**
 * in_data - inicialize the struct with the info of the program
 * @string: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void in_data(data_program *string, int argc, char *argv[], char **env)
{
	int i = 0;

	string->program_name = argv[0];
	string->input_line = NULL;
	string->comand_name = NULL;
	string->exec_counter = 0;
	if (argc == 1)
		string->file_descriptor = STDIN_FILENO;
	else
	{
		string->file_descriptor = open(argv[1], O_RDONLY);
		if (string->file_descriptor == -1)
		{
			_printe(string->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	string->tokens = NULL;
	string->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			string->env[i] = str_duplicate(env[i]);
		}
	}
	string->env[i] = NULL;
	env = string->env;

	string->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		string->alias_list[i] = NULL;
	}
}
/**
 * teamwk - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @string: its a infinite loop that shows the prompt
 */
void teamwk(char *prompt, data_program *string)
{
	int error_code = 0, string_len = 0;

	while (++(string->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(string);

		if (error_code == EOF)
		{
			free_all_data(string);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(string);
			expand_variables(string);
			tokenize(string);
			if (string->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(string);
				if (error_code != 0)
					_print_error(error_code, string);
			}
			current_data_free(string);
		}
	}
}
