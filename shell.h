#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h> 
#include <fcntl.h> 


<<<<<<< HEAD
/************* STRUCTURES **************/
=======
#include "macros.h" 
>>>>>>> 03d8dc6e7ec8504807aca1647c9911b57e4bd60f

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @comand_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *comand_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_program *string);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void in_data(data_program *string, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void teamwk(char *prompt, data_program *string);

/* Print the prompt in a new line */
void con_ctrl_c(int opr, UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the standar input*/
<<<<<<< HEAD
int _getline(data_program *data);
=======
int _getline(data_program *string);
>>>>>>> 03d8dc6e7ec8504807aca1647c9911b57e4bd60f

/* split the each line for the logical operators if it exist */
int check_logic(char *array_commands[], int i, char array_operators[]);


/*======== expand.c ========*/

/* expand variables */
void expand_variables(data_program *data);

/* expand aliases */
void expand_alias(data_program *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(data_program *data);

/* Creates a pointer to a part of a string */
char *tokes(char *line, char *delim);


/*======== execution.c ========*/

/* Execute a command with its entire path */
int execute(data_program *data);


/*======== builtin.c ========*/

/* If match a builtin, executes it */
int builtins_list(data_program *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
<<<<<<< HEAD
char **tokenize_path(data_program *data);

/* Search for program in path */
int find_program(data_program *data);
=======
char **tokeize_path(data_program *data);

/* Search for program in path */
int program(data_program *data);
>>>>>>> 03d8dc6e7ec8504807aca1647c9911b57e4bd60f


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void pointers_of_array_free(char **directories);

/* Free the fields needed each loop */
<<<<<<< HEAD
void free_recurrent_data(data_program *data);

/* Free all field of the data */
void free_all_data(data_program *data);
=======
void current_data_free(data_program *data);

/* Free all field of the data */
void data_to_free(data_program *data);
>>>>>>> 03d8dc6e7ec8504807aca1647c9911b57e4bd60f


/************** BUILTINS **************/


/*======== built_more.c ========*/

/* Close the shell */
int builtin_exit(data_program *data);

/* Change the current directory */
int builtin_cd(data_program *data);

/* set the work directory */
int set_work_directory(data_program *data, char *new_dir);

/* show help information */
int builtin_help(data_program *data);

/* set, unset and show alias */
int builtin_alias(data_program *data);


/*======== built_en.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(data_program *data);

/* create or override a variable of environment */
int builtin_set_env(data_program *data);

/* delete a variable of environment */
int builtin_unset_env(data_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== manage_env.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, data_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_program *data);

/* prints the current environ */
void print_environ(data_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, data_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


/*======== alias_manage.c ========*/

/* print the list of alias */
int print_alias(data_program *data, char *alias);

/* get the alias name */
char *get_alias(data_program *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, data_program *data);


#endif /* SHELL_H */
