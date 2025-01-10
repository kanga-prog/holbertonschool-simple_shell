#include "simple_shell.h"

/**
 * env_c - Prints the current environment variables.
 *
 * This function iterates through the `environ` global variable
 * and prints each environment variable in the format:
 * "KEY=VALUE" followed by a newline.
 * It does not take any arguments and does not return a value.
 */
void _env(void)
{
    char **env = environ;  /* Pointeur vers le tableau d'environnement */

    while (*env)  /* Tant qu'il y a des variables d'environnement */
    {
        printf("%s\n", *env);  /* Afficher chaque variable */
        env++;  /* Passer à la suivante */
    }
}
