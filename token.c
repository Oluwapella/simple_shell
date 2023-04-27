#include "shell.h"
/**
 * tokes - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *tokes(char *line, char *delim)
{
	int i;
	static char *ptr;
	char *cpptr;

	if (line != NULL)
		ptr = line;
	for (; *ptr != '\0'; ptr++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*ptr == delim[i])
			break;
		}
		if (delim[i] == '\0')
			break;
	}
	cpptr = ptr;
	if (*cpptr == '\0')
		return (NULL);
	for (; *ptr != '\0'; ptr++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*ptr == delim[i])
			{
				*ptr = '\0';
				ptr++;
				return (cpptr);
			}
		}
	}
	return (cpptr);
}
