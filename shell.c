#include "simple_shell.h"

#define MAX_COMMAND_LENGTH 1024

/**
 * main - Entry point for the simple shell program.
 *
 * This function continually prompts the user for input,
 * parses the input, and executes the appropriate command(s).
 *
 * Return: 0 on success.
 */
int main(void)
{
	char input[MAX_COMMAND_LENGTH];
	ssize_t bytes_read;

	while (1)
	{
		/* Print the prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9); /* Using write to print prompt */
		}

		/* Read the input only if in interactive mode or if input is from stdin */
		if (isatty(STDIN_FILENO))
		{
			/* Use read() to read input */
			bytes_read = read(STDIN_FILENO, input, sizeof(input) - 1);
			if (bytes_read == 0)  /* EOF (Ctrl+D) encountered */
				break;

			if (bytes_read < 0)  /* Read error */
			{
				perror("read");
				exit(1);
			}

			/* Null-terminate the string after reading */
			input[bytes_read] = '\0';

			/* Remove the trailing newline character, if any */
			input[strcspn(input, "\n")] = 0;
		}
		else
		{
			/* In non-interactive mode, assume input is already provided (stdin redirected) */
			bytes_read = read(STDIN_FILENO, input, sizeof(input) - 1);
			if (bytes_read == 0)  /* EOF encountered */
				break;

			if (bytes_read < 0)  /* Read error */
			{
				perror("read");
				exit(1);
			}

			input[bytes_read] = '\0';  /* Null-terminate the string */
			input[strcspn(input, "\n")] = 0;  /* Remove newline if present */
		}

		/* Parse the input and execute the command(s) */
		parse_and_execute(input);

		/* If in non-interactive mode, exit after executing the command */
		if (!isatty(STDIN_FILENO))
		{
			break;
		}
	}

	return (0);
}
