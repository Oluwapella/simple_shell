#include "shell.h"

/**
 * main - functions
 * @argc: its counts argument
 * @argv:argument pass to the shell
 *@env: environment varables
 */
int main(int agrc, char **agrv, char **env)
{
	if(agrc == 1)
		teamwk(agrv, env);
	return (0);
}
