#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point for the simple shell
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
		/* Print prompt */
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Get the command line input from user */
		read = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl+D) */
		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break; /* Exit the shell */
		}

		/* Remove trailing newline character from the input */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Create a child process to execute the command */
		pid = fork();

		if (pid == -1)
		{
			perror("fork failed");
			exit(1); /* Exit if fork fails */
		}
		else if (pid == 0)  /* Child process */
		{
			/* Try to execute the command */
			if (execve(line, &line, NULL) == -1)
			{
				/* If execve fails, print an error */
				perror("./shell");
				exit(1);
			}
		}
		else  /* Parent process */
		{
			wait(&status);  /* Wait for the child to terminate */
		}
	}

	/* Free allocated memory */
	free(line);

	return (0);  /* Successful exit */
}
