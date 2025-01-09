#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 100


/* Function prototypes */

/* Function to remove quotes from an argument */
void remove_quotes(char *arg);

/* Function to find the full path of a command */
char *find_full_path(char *command);

/* Function to execute a single command */
void execute_command(char *command);

/* Function to execute pipe command */
void execute_pipe(char *command1, char *command2);

/* Function to parse and execute commands */
void parse_and_execute(char *input);

#endif /* SIMPLE_SHELL_H */
