#include "shell.h"  /* Inclure le fichier d'en-tête personnalisé */
#include <errno.h>


/* Définition de constantes */

#define BUFFER_SIZE 1024

/* Déclaration des fonctions pour l'historique */
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
            perror(command);  /* Afficher une erreur si execve échoue */
            _exit(1);  /* Terminer le processus enfant après l'erreur */
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
 * handle_input - Gère l'entrée de l'utilisateur et l'exécution des commandes.
 * @line: La ligne de commande à traiter.
 */
void handle_input(char *line)
{
    /* Déclaration des variables avant tout code */
    char *command;
    char *args;
    char *dir;

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

    command = line;
    args = strchr(line, ' ');  /* Trouver un espace entre la commande et ses arguments */

    if (args != NULL)
    {
        *args = '\0';  /* Terminer la commande à cet endroit */
    }

    /* Si la commande est 'echo' ou 'ls' */
    if (strcmp(command, "echo") == 0)
    {
        if (args != NULL)
        {
            printf("%s\n", args);  /* Afficher les arguments de echo */
        }
    }
    else if (strcmp(command, "ls") == 0)
    {
        list_directory_contents();  /* Afficher le contenu du répertoire */
    }
    else
    {
        /* Si la commande commence par /, c'est un chemin absolu */
        if (command[0] == '/')
        {
            if (access(command, X_OK) == 0)
            {
                execute_command(command);
            }
            else
            {
                fprintf(stderr, "%s: No such file or directory\n", command);
            }
        }
        else
        {
            /* Chercher la commande dans le PATH */
            char *path = getenv("PATH");
            if (path != NULL)
            {
                char *path_copy = malloc(strlen(path) + 1);  /* Dupliquer la chaîne PATH */
                if (path_copy == NULL)
                {
                    perror("malloc");
                    exit(1);
                }
                strcpy(path_copy, path);
                dir = strtok(path_copy, ":");
                while (dir != NULL)
                {
                    char full_path[BUFFER_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

                    /* Vérifier si le fichier est exécutable */
                    if (access(full_path, X_OK) == 0)
                    {
                        execute_command(full_path);
                        free(path_copy);  /* Libérer la mémoire allouée pour path_copy */
                        return;
                    }

                    dir = strtok(NULL, ":");
                }
                free(path_copy);  /* Libérer la mémoire allouée pour path_copy */
            }
            else
            {
                fprintf(stderr, "%s: No such file or directory\n", command);
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

