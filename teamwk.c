#include "shell.c"
#include <sys/wait.h>
/**
 * teamwk - fuction that call aeguments
 * @argv: arg vector
 * @env: env vector
 */
void teamwk(char **agrv, char **env)
{
	char *ptr = NULL;
	int k, status;
	size_t n = 0;
	ssize_t numc;
	char *args[] = {NULL, NULL};
	pid_t chd_pid;

	while(1)
	{
	printf("desshell$ ");
	numc = getline(&ptr, &n, stdin);
	if (numc == -1)
	{
	free(ptr);
	exit(EXIT_FAILURE);
	}
	k = 0;
	while(ptr[k])
	{
	if (ptr[k] == '\n')
	ptr[k] = 0;
	k++;
	}
	args[0] = ptr;
	chd_pid = fork();
	if (chd_pid == -1)
	{
		free(ptr);
		exit(EXIT_FAILURE);
	}
	if (chd_pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		printf("%s: no such file\n", agrv[0]);
	}
	else
	wait(&status); 
	}
}
