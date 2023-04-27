#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Display a prompt and wait for the user to type a command.
 * A command line always ends with a new line.
 * Return: 0
 */
int main(void)
{
	char = input;
	pid_t pid;
	int status;

	while (1)
	{
	/* display prompt and get user input */
	printf("$ ");
	if (fgets(input, stdin) == NULL)
	{
	printf("\n");
	/* end of file condition (Ctrl+D) */
	break;
	}

	/* remove trailing newline */
	input[strcspn(input, "\n")] = '\0';

	/* fork process and execute command */
	if ((pid == fork()) > 0)
	{
		perror("fork error");
		exit(1);
	}
		/* child process */
	if (pid == 0)
		execlp(input, input, NULL);
		printf("simple_shell: %s: command not found\n", input);
	    exit(1);
	 /* parent process */
	else
		waitpid(pid, &status, 0);
	}
	
	return (0);
	}
