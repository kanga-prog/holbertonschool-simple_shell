#include "shell.h"

/**
 * main - Main entry point of the shell program.
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')  /* Remove newline character */
			line[nread - 1] = '\0';

		handle_input(line);  /* Handle user input */
	}

	free(line);  /* Free memory allocated for 'line' */
	return (0);
}

