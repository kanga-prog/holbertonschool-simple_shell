#include "shell.h"

/**
 * execute_command - Exécute une commande en créant un processus enfant.
 * @command: La commande à exécuter.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}

	if (pid == 0)  /* Processus enfant */
	{
		char *argv[2];
		argv[0] = command;
		argv[1] = NULL;

		/* Exécuter la commande */
		if (execve(command, argv, NULL) == -1)
		{
			perror(command);  /* Afficher une erreur si execve échoue */
			exit(1);  /* Terminer le processus enfant après l'erreur */
		}
	}
	else  /* Processus parent */
	{
		wait(NULL);  /* Attendre la fin du processus enfant */
	}
}

/**
 * handle_input - Gère l'entrée de l'utilisateur et l'exécution des commandes.
 * @line: La ligne de commande à traiter.
 */
void handle_input(char *line)
{
	/* Si la commande est vide, on ignore */
	if (strlen(line) == 0)
	{
		return;
	}

	/* Si la commande est exit, on quitte le shell */
	if (strcmp(line, "exit") == 0)
	{
		exit(0);
	}

	/* Si la commande est un fichier exécutable dans le répertoire courant */
	if (access(line, X_OK) == 0)
	{
		execute_command(line);
	}
	else
	{
		/* Chercher la commande dans le PATH */
		char *path = getenv("PATH");
		if (path != NULL)
		{
			char *path_copy = strdup(path);  /* Dupliquer la chaîne PATH*/
			char *dir = strtok(path_copy, ":");
			while (dir != NULL)
			{
				char full_path[BUFFER_SIZE];
				snprintf(full_path, sizeof(full_path), "%s/%s", dir, line);

				/* Vérifier si le fichier est exécutable */
				if (access(full_path, X_OK) == 0)
				{
					execute_command(full_path);
					break;
				}

				dir = strtok(NULL, ":");
			}
			free(path_copy);  /* Libérer la mémoire allouée pour path_copy*/
		}
		else
		{
			fprintf(stderr, "./shell: No such file or directory\n");
		}
	}
}

/**
 * main - Point d'entrée principal du programme shell.
 *
 * Return: Toujours 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			printf("\n");
			break;
		}

		/* Supprimer le caractère de nouvelle ligne à la fin de la commande */
		if (line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';
		}

		handle_input(line);  /* Traiter l'entrée de l'utilisateur*/
	}

	free(line);  /* Libérer la mémoire allouée pour 'line'*/
	return 0;
}

