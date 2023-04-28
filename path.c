#include "shell.h"

int ch_file(char *p_path);

/**
 * program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int program(data_program *data)
{
	int i = 0, cd = 0;
	char **process;

	if (!data->comand_name)
		return (2);

	if (data->comand_name[0] == '/' || data->comand_name[0] == '.')
		return (ch_file(data->comand_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->comand_name);
	if (!data->tokens[0])
		return (2);

	process = tokenize_path(data);/* search in the PATH */

	if (!process || !process[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; process[i]; i++)
	{
		process[i] = str_concat(process[i], data->tokens[0]);
		cd = ch_file(process[i]);
		if (cd == 0 || cd == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(process[i]);
			pointers_of_array_free(process);
			return (cd);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	pointers_of_array_free(process);
	return (cd);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenize_path(data_program *data)
{
	int i = 0;
	int counter = 2;
	char **tokens = NULL;
	char *PATHS;

	/* get the PATH value*/
	PATHS = env_get_key("PATH", data);
	if ((PATHS == NULL) || PATHS[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATHS = str_duplicate(PATHS);

	/* find the number of directories in the PATH */
	for (i = 0; PATHS[i]; i++)
	{
		if (PATHS[i] == ':')
			counter++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter);

	/*tokenize and duplicate each token of path*/
	i = 0;
	tokens[i] = str_duplicate(strtok(PATHS, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(strtok(NULL, ":"));
	}

	free(PATHS);
	PATHS = NULL;
	return (tokens);

}

/**
 * ch_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @p_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int ch_file(char *p_path)
{
	struct stat sb;

	if (stat(p_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(p_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
