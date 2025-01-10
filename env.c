#include "simple_shell.h"

/**
 * env_c - Prints the current environment variables.
 *
 * This function iterates through the `environ` global variable
 * and prints each environment variable in the format:
 * "KEY=VALUE" followed by a newline.
 * It does not take any arguments and does not return a value.
 */
void env_c(void)
{
    extern char **environ;  /* Global variable that holds the environment */
    char **env = environ;   /* Pointer to the environment variables */

    /* Loop through the environment and print each variable */
    while (*env)
    {
        printf("%s\n", *env);  /* Print each environment variable */
        env++;  /* Move to the next environment variable */
    }
}
