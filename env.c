#include "simple_shell.h"

/**
 * env_c - Prints the current environment variables.
 *
 * This function iterates through the `environ` global variable
 * and prints each environment variable in the format:
 * "KEY=VALUE" followed by a newline.
 * It does not take any arguments and does not return a value.
 */
int env_c(void)
{
	extern char **environ;
	size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);

}
