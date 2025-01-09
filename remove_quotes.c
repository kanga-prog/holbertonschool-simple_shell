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
	int i = 0;
	char temp[MAX_ARGS]; /* Temporary array to hold the result */

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

	/* Copy the content into the temp array without quotes */
	while (start <= end)
	{
		temp[i++] = *start++;
	}

	/* Null-terminate the result */
	temp[i] = '\0';

	/* Copy the result back to the original argument */
	i = 0;
	while (temp[i] != '\0')
	{
		arg[i] = temp[i];
		i++;
	}

	/* Null-terminate the final result */
	arg[i] = '\0';
}

