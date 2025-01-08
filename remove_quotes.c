#include "simple_shell.h"

/**
 * remove_quotes - Removes quotes from a given argument string.
 * @arg: The argument string to remove quotes from.
 *
 * This function checks the start and end of the argument string for
 * quotes (both single and double quotes) and removes them.
 */
void remove_quotes(char *arg)
{
	char *start = arg;
	char *end = arg + strlen(arg) - 1;

	/* Skip leading quote */
	while (*start == '"' || *start == '\'')
	{
		start++;
	}

	/* Skip trailing quote */
	while (*end == '"' || *end == '\'')
	{
		end--;
	}

	/* Shift the content to remove the quotes */
	memmove(arg, start, end - start + 1);
	arg[end - start + 1] = '\0';
}
