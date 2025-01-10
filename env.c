#include "simple_shell.h"

/**
 * env_c - Prints the current environment variables.
 *
 * This function iterates through the `environ` global variable
 * and prints each environment variable in the format:
 * "KEY=VALUE" followed by a newline.
 * It does not take any arguments and does not return a value.
 */

extern char **environ;

void _env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}
