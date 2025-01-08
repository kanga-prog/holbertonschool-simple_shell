#include "shell.h"

/**
 * execute_builtin - Executes built-in commands like 'echo' and 'ls'.
 * @command: The command to execute.
 * @args: Arguments associated with the command.
 */
void execute_builtin(char *command, char *args)
{
	if (strcmp(command, "echo") == 0)
	{
		if (args != NULL)
		{
			printf("%s\n", args);  /* Print arguments for echo */
		}
	}
	else if (strcmp(command, "ls") == 0)
	{
		list_directory_contents();  /* Display the contents of the directory */
	}
}

/**
 * handle_input - Handles user input and executes commands.
 * @line: The input command to process.
 */
void handle_input(char *line)
{
	char *command;
	char *args;

	if (strlen(line) == 0)  /* If the command is empty, return */
		return;

	if (strcmp(line, "exit") == 0)  /* Exit the shell if 'exit' command */
		exit(0);

	while (*line == ' ')  /* Remove leading spaces */
		line++;

	command = line;
	args = strchr(line, ' ');

	if (args != NULL)  /* Split command and arguments */
	{
		*args = '\0';
		args++;
	}

	execute_builtin(command, args);

	if (command[0] == '/') /* check if path is absolute */
	{
		if (access(command, X_OK) == 0)  /* check if it's exec */
			execute_command(command);
		else
			fprintf(stderr, "%s: No such file or directory\n", command);
	}
	else
	{
		if (search_in_path(command) == -1)  /* Search in PATH */
			fprintf(stderr, "%s: command not found\n", command);
	}
}
