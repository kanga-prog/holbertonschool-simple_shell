#include "shell.h"

/**
 * search_in_path - Searches for a command in the PATH.
 * @command: The command to search for.
 * Return: 0 if found, -1 if not found.
 */

#define BUFFER_SIZE 1024

int search_in_path(char *command)
{
	char *path;
	char *path_copy;
	char *dir;
	char full_path[BUFFER_SIZE];

	path = getenv("PATH");

	if (path == NULL)
		return (-1);

	path_copy = malloc(strlen(path) + 1);  /* Duplicate the PATH string */

	if (path_copy == NULL)
	{
		perror("malloc");
		exit(1);
	}

	strcpy(path_copy, path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)  /* Check if file is executable */
		{
			execute_command(full_path);  /* Execute the command */
			free(path_copy);  /* Free allocated memory for path_copy */
			return (0);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);  /* Free allocated memory for path_copy */
	return (-1);
}
