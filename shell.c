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

	while (1)
	{
		/* Print the prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
		}
		/* Read the input */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			perror("fgets");
			exit(1);
		}

		/* Remove the trailing newline character */
		input[strcspn(input, "\n")] = 0;

		/* Exit the shell if the user types "exit" */
		if (strcmp(input, "exit") == 0)
		{
			break;
		}

		/* Parse the input and execute the command(s) */
		parse_and_execute(input);
	}

	return (0);
}
