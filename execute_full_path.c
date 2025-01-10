#include "simple_shell.h"
/**
 * find_full_path - Finds the full path of a command.
 * @command: The command for which to find the full path.
 * Return: The full path of the command or NULL if not found.
 */
char *find_full_path(char *command)
{
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];
	FILE *file;
	int i = 0;

	/* Loop through the environment variables to find PATH */
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;  /* Skip over "PATH=" */
			break;
		}
		i++;
	}

	if (path == NULL)
	{
		perror("PATH not found in environment");
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
    extern char *program_name;

    pid = fork(); /* Create a new child process */

    if (pid == 0) /* Child process */
    {
        /* Redirect input if necessary */
        if (input_fd != STDIN_FILENO)
        {
            int new_input_fd = open(command, O_RDONLY); /* Open the file for reading */
            if (new_input_fd == -1)
            {
                perror("open input");
                exit(1);
            }
            close(STDIN_FILENO);  /* Close standard input */
            if (dup(new_input_fd) == -1)  /* Redirect stdin to the new file descriptor */
            {
                perror("dup input");
                exit(1);
            }
            close(new_input_fd);  /* Close the file descriptor after use */
        }

        /* Redirect output if necessary */
        if (output_fd != STDOUT_FILENO)
        {
            int new_output_fd = open(command, O_WRONLY | O_CREAT | O_TRUNC, 0644); /* Open the file for writing */
            if (new_output_fd == -1)
            {
                perror("open output");
                exit(1);
            }
            close(STDOUT_FILENO);  /* Close standard output */
            if (dup(new_output_fd) == -1)  /* Redirect stdout to the new file descriptor */
            {
                perror("dup output");
                exit(1);
            }
            close(new_output_fd);  /* Close the file descriptor after use */
        }

        /* Execute the command */
        if (command[0] == '/')
        {
            if (execve(command, args, environ) == -1)
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
                fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
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
        wait(NULL); /* Wait for the child process to finish */
    }
}
