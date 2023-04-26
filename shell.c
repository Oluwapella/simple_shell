#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char **argv)
{
	char *prompts = "(teampromts) $ ";
	char *lineptr;
	char **argv;
	size_t n = 0;
	ssize_t nchars;
	char *lineptr_cop = NULL;
	const char *delimete = " \n";
	int num_tken = 0;
	char *tken;
	int k;


	while(1){
	printf("%s",prompts);
	nchars = getline(&lineptr, &n, stdin);
	if (nchars == -1){
		printf("shell,exiting\n");
			return (-1);
	}
	lineptr_cop = malloc(sizeof(char) * nchars_read);
        if (lineptr_cop == NULL){
            perror("tsh:allocation error");
            return (-1);
	} 
	 string(lineptr_cop, lineptr);
	  tken = strtok(lineptr, delimete);

        while (tken != NULL){
            num_tken++;
            tken = strtok(NULL, delimete);
        }
        num_tkens++;
	argv = malloc(sizeof(char *) * num_tkens);
	tken = strtok(lineptr_cop, delimete);
	 for (i = 0; tken != NULL; i++){
            argv[k] = malloc(sizeof(char) * strlen(tken));
            strcpy(argv[k], token);

            tken = strtok(NULL, delimete);
        }
        argv[k] = NULL;

	exec(argv);


	
        free(lineptr_cop);
        free(lineptr);
        }
	}
	return (0);
}
