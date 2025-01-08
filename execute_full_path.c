#include "simple_shell.h"
/**
 * find_full_path - Finds the full path of a command.
 * @command: The command for which to find the full path.
 * Return: The full path of the command or NULL if not found.
 */
char *find_full_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy;
	char *dir;
	char full_path[1024];
	FILE *file;

	if (path == NULL)
	{
		perror("getenv");
		return (NULL);
	}
	path_copy = malloc(strlen(path) + 1); /* Allocate memory for path copy */
	if (path_copy == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	strcpy(path_copy, path);  /* Copy the PATH variable */

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		file = fopen(full_path, "r");
		if (file != NULL)
		{
			fclose(file);
			free(path_copy);
			return (strdup(full_path)); /* Return the full path */
		}
		dir = strtok(NULL, ":"); /* Move to the next directory */
	}
	free(path_copy);
	return (NULL); /* Return NULL if command is not found */
}

/**
 * execute_command - Executes a command with arguments.
 * @command: The command to execute.
 * @args: The arguments for the command.
 * @input_fd: The input file descriptor.
 * @output_fd: The output file descriptor.
 *
 * This function forks a new process and executes the given command using
 * execve(). It handles input and output redirection if necessary.
 */
void execute_command(char *command, char *args[], int input_fd, int output_fd)
{
	pid_t pid;
	char *full_path;

	pid = fork();

	if (pid == 0) /* Child process */
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}

		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		if (command[0] == '/')
		{
			if (execve(command, args, NULL) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			full_path = find_full_path(command);
			if (full_path == NULL)
			{
				perror("Command not found");
				exit(1);
			}
			if (execve(full_path, args, NULL) == -1)
			{
				perror("execve");
				free(full_path);
				exit(1);
			}
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		wait(NULL);
	}
}
