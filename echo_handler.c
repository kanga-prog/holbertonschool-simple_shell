#include "shell.h"

/**
 * remove_quotes - Removes quotes (single and double) from the input string.
 * @str: The string to remove quotes from.
 *
 * Return: A new string with quotes removed.
 */
char *remove_quotes(char *str)
{
	int len = strlen(str);
	char *new_str = malloc(len + 1);  /* Allocate memory for the new string */
	int i = 0, j = 0;

	if (!new_str)
	{
		perror("malloc");
		exit(1);
	}

	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		{
			i++;  /* Skip quotes */
		}
		else
		{
			new_str[j++] = str[i++];
		}
	}
	new_str[j] = '\0';

	return (new_str);
}

/**
 * echo_command - Custom implementation of echo that ignores quotes.
 * @args: The arguments to be echoed.
 */
void echo_command(char *args)
{
	char *str = remove_quotes(args);  /* Remove quotes around the argument */

	printf("%s\n", str);  /* Print the argument */
	free(str);  /* Free the memory allocated for the argument */
}
