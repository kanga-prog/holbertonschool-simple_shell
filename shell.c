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

    if (pid == 0)
    {
        char *argv[2];

        argv[0] = command;
        argv[1] = NULL;

        if (execve(command, argv, NULL) == -1)
        {
            perror(command);
        }

        exit(1);
    }
    else
    {
        wait(NULL);
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

        if (line[nread - 1] == '\n')
        {
            line[nread - 1] = '\0';
        }

        if (strlen(line) == 0)
        {
            continue;
        }

        if (access(line, X_OK) == 0)
        {
            execute_command(line);
        }
        else
        {
            fprintf(stderr, "./shell: No such file or directory\n");
        }
    }

    free(line);
    return (0);
}
