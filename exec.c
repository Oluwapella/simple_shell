#include "main.h"

void execmed(char **argv){
    char *comand = NULL;

    if (argv){
        /* get the command */
        comand = argv[0];

        /* execute the command with execve */
        if (execmed(comand, argv, NULL) == -1){
            perror("Error:");
        };
    }

}
