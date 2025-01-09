#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 100



/* Function to execute a single command */
void execute_command(char *command);


#endif /* SIMPLE_SHELL_H */
