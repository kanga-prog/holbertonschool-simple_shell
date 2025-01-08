#include "shell.h"

/**
 * list_directory_contents - Displays the contents of the current directory.
 * Ignores hidden files and "." and "..".
 */
void list_directory_contents(void)
{
	struct dirent *entry;
	DIR *dp = opendir(".");  /* Open the current directory */

	if (dp == NULL)
	{
		perror("opendir");  /* Print error if directory can't be opened */
		return;
	}

	while ((entry = readdir(dp)) != NULL)
	{
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
		{
			if (entry->d_name[0] != '.')  /* Ignore hidden files and directories */
				printf("%s  ", entry->d_name);
		}
	}

	printf("\n");
	closedir(dp);  /* Close the directory */
}

