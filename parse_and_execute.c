#include "simple_shell.h"

/**
 * parse_and_execute - Parses the input and executes command.
 * @input: The input string containing one or more commands.
 *
 * This function splits the input string by pipes ('|') and processes each
 * command individually. It handles commands with and without pipes.
 */
void parse_and_execute(char *input)
{
			char *token;
			char *args[MAX_ARGS];
			int i = 0;

			/* Tokenize the command and arguments */
			token = strtok(input, " ");

			while (token != NULL)
			{
				remove_quotes(token);  /* Remove quotes around the argument */
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;

			execute_command(args[0], args, STDIN_FILENO, STDOUT_FILENO);
}
