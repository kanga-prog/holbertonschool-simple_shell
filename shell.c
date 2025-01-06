#include "shell.h"

/**
 * main - The main shell program that handles command execution
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;    /* Input command line */
	size_t len = 0;       /* Length of the input */
	ssize_t read;         /* Number of characters read */
	pid_t pid;            /* Process ID */
	int status;           /* Process status */

	/* Display the prompt */
	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break; /* Exit the shell */
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			free(line);  /* Free allocated memory */
			exit(1);
		}
		else if (pid == 0)  /* Child process */
		{
			char *args[] = {line, NULL};
			if (execve(line, args, NULL) == -1)
			{
				perror("./hsh");
				free(line);  /* Free allocated memory */
				exit(1);
			}
		}
		else
		{
			wait(&status);  /* Wait for the child to terminate */
		}
	}

	free(line);
	return (0);
}
