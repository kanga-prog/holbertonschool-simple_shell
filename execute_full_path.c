#include "simple_shell.h"

/**
 * execute_command - Executes a command with arguments.
 * @command: The command to execute.
 * @args: The arguments for the command.
 * @input_fd: The input file descriptor.
 * @output_fd: The output file descriptor.
 *
 * This function forks a new process and executes the given command using
 * execve(). It handles input and output redirection if necessary.
 */
void execute_command(char *command)
{
    pid_t pid;
    char **args = malloc(2 * sizeof(char *));

    if (args == NULL)
    {
        perror("malloc");
        exit(1);
    }

    args[0] = command;
    args[1] = NULL;

    if ( args[0] == NULL)
    {
        printf("./shell: No such file or directory\n");
        free(args);
        fflush(stdout);
        exit(1);
    }

    pid = fork();
    if (pid == 0) /* Child process */
    {
        if (execve(args[0], args, NULL) == -1)
        {
            printf("./shell: No such file or directory\n");
            exit(1);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        wait(NULL); /* Parent waits for the child to finish */
    }
    free(args);
}
