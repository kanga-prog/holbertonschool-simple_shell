#include "shell.h"  /* Inclure le fichier d'en-tête personnalisé */
#include <errno.h>


/* Déclaration d'une variable pour l'historique */
char *history[MAX_HISTORY];
int history_index = 0;

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
			/* Afficher une erreur spécifique si execve échoue */
			if (errno == ENOENT)  /* Fichier ou répertoire introuvable */
			{
				fprintf(stderr, "%s: No such file or directory\n", command);
			}
			else if (errno == EACCES)  /* Pas la permission d'exécuter */
			{
				fprintf(stderr, "%s: Permission denied\n", command);
			}
			else
			{
				perror(command);  /* Autres erreurs générales */
			}
			exit(1);  /* Terminer le processus enfant après l'erreur */
		}
	}
	else  /* Processus parent */
	{
		wait(NULL);  /* Attendre la fin du processus enfant */
	}
}

/**
 * list_directory_contents - Affiche le contenu du répertoire actuel sans les fichiers cachés ni . et ..
 */
void list_directory_contents(void)
{
	struct dirent *entry;
	DIR *dp = opendir(".");  /* Ouvrir le répertoire courant */

	if (dp == NULL)
	{
		perror("opendir");
		return;
	}

	/* Lire et afficher le contenu du répertoire, en ignorant . et .. */
	while ((entry = readdir(dp)) != NULL)
	{
		/* Filtrer les entrées . et .. */
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
		{
			/* Afficher uniquement les fichiers et répertoires (sans fichiers cachés) */
			if (entry->d_name[0] != '.')  /* Ignore les fichiers et répertoires cachés */
			{
				printf("%s  ", entry->d_name);
			}
		}
	}

	printf("\n");
	closedir(dp);  /* Fermer le répertoire */
}

/**
 * add_to_history - Ajoute une commande à l'historique.
 * @line: La commande à ajouter à l'historique.
 */
void add_to_history(const char *line)
{
	int i;

	if (history_index < MAX_HISTORY)
	{
		history[history_index++] = strdup(line);  /* Copier la ligne dans l'historique */
	}
	else
	{
		free(history[0]);  /* Supprimer la première entrée si l'historique est plein */
		for (i = 1; i < MAX_HISTORY; i++)
		{
			history[i - 1] = history[i];
		}
		history[MAX_HISTORY - 1] = strdup(line);  /* Ajouter la nouvelle commande */
	}
}

/**
 * print_history - Affiche l'historique des commandes.
 */
void print_history()
{
	int i;

	for (i = 0; i < history_index; i++)
	{
		printf("%d %s\n", i + 1, history[i]);
	}
}

/**
 * handle_input - Gère l'entrée de l'utilisateur et l'exécution des commandes.
 * @line: La ligne de commande à traiter.
 */
void handle_input(char *line)
{
	char *command;
	char *args;
	int background = 0;

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

	/* Supprimer les espaces inutiles avant et après la commande */
	while (*line == ' ')  /* Supprimer les espaces au début */
		line++;

	/* Vérifier si la commande doit être exécutée en arrière-plan */
	if (line[strlen(line) - 1] == '&')
	{
		background = 1;
		line[strlen(line) - 1] = '\0';  /* Supprimer le '&' */
	}

	command = line;
	args = strchr(line, ' ');  /* Trouver un espace entre la commande et ses arguments */

	if (args != NULL)
	{
		*args = '\0';  /* Terminer la commande à cet endroit */
		args++;  /* Passer aux arguments */
	}

	/* Traitement des commandes comme echo, ls, cd, etc. */
	if (strcmp(command, "echo") == 0)
	{
		printf("%s\n", args);  /* Afficher les arguments de echo */
	}
	else
	{
		if (command[0] == '/')
		{
			if (access(command, X_OK) == 0)
			{
				if (background)
				{
					if (fork() == 0)  /* Processus enfant */
					{
						execute_command(command);
						exit(0);
					}
				}
				else
				{
					execute_command(command);  /* Commande normale */
				}
			}
			else
			{
				fprintf(stderr, "%s: No such file or directory\n", command);  /* Erreur si le fichier est introuvable */
			}
		}
		else
		{
			/* Chercher la commande dans le PATH */
			char *path = getenv("PATH");
			if (path != NULL)
			{
				char *path_copy = strdup(path);  /* Dupliquer la chaîne PATH */
				char *dir = strtok(path_copy, ":");
				int found = 0;

				while (dir != NULL)
				{
					char full_path[BUFFER_SIZE];
					snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

					if (access(full_path, X_OK) == 0)
					{
						if (background)
						{
							if (fork() == 0)  /* Processus enfant en arrière-plan */
							{
								execute_command(full_path);
								exit(0);
							}
						}
						else
						{
							execute_command(full_path);
						}
						found = 1;
						break;
					}

					dir = strtok(NULL, ":");
				}

				if (!found)
				{
					fprintf(stderr, "%s: No such file or directory\n", command);
				}

				free(path_copy);  /* Libérer la mémoire allouée pour path_copy */
			}
			else
			{
				fprintf(stderr, "No such file or directory: %s\n", command);
			}
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

		handle_input(line);  /* Traiter l'entrée de l'utilisateur */
	}

	free(line);  /* Libérer la mémoire allouée pour 'line' */
	return 0;
}

