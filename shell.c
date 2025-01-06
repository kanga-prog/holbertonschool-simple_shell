#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * execute_command - Executes a command by forking a child process.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0)  /* Process enfant*/
    {
        char *argv[2];

        argv[0] = command;
        argv[1] = NULL;

        /* Exécution de la commande*/
        if (execve(command, argv, NULL) == -1)
        {
            perror(command);  /* Affiche une erreur si execve échoue*/
            exit(1);  /* Terminer le processus enfant après l'erreur*/
        }
    }
    else  /* Processus parent*/
    {
        wait(NULL);  /* Attendre la fin du processus enfant*/
    }
}

/**
 * main - Main entry point of the shell program.
 * Return: Always 0.
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

        /* Supprimer le caractère de nouvelle ligne à la fin de la commande*/
        if (line[nread - 1] == '\n')
        {
            line[nread - 1] = '\0';
        }

        /* Si la commande est vide, on recommence la boucle*/
        if (strlen(line) == 0)
        {
            continue;
        }

        /* Si la commande est un fichier exécutable*/
        if (access(line, X_OK) == 0)
        {
            execute_command(line);
        }
        else
        {
            /* Chercher dans le PATH si la commande existe*/
            char *path = getenv("PATH");
            if (path != NULL)
            {
                char *dir = strtok(path, ":");
                while (dir != NULL)
                {
                    char full_path[BUFFER_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, line);

                    /* Vérifier si le fichier est exécutable*/
                    if (access(full_path, X_OK) == 0)
                    {
                        execute_command(full_path);
                        break;
                    }

                    dir = strtok(NULL, ":");
                }
            }
            else
            {
                fprintf(stderr, "./shell: No such file or directory\n");
            }
        }
    }

    free(line);
    return 0;
}

