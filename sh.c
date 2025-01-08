#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 100

/* Function to remove quotes from an argument */
void remove_quotes(char *arg)
{
    char *start = arg;
    char *end = arg + strlen(arg) - 1;

    while (*start == '"' || *start == '\'') start++;
    while (*end == '"' || *end == '\'') end--;

    memmove(arg, start, end - start + 1);
    arg[end - start + 1] = '\0';
}

/* Function to find the full path of a command */
char *find_full_path(char *command)
{
    char *path = getenv("PATH");
    char *path_copy = malloc(strlen(path) + 1);
    char *dir, full_path[1024];

    if (path_copy == NULL)
    {
        perror("malloc");
        return NULL;
    }

    strcpy(path_copy, path);

    dir = strtok(path_copy, ":");  /* Split PATH by ":" */
    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return strdup(full_path);  /* Return the full path */
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;  /* Return NULL if command not found */
}

/* Function to execute a single command */
void execute_command(char *command, char *args[], int input_fd, int output_fd)
{
    pid_t pid;
    char *full_path;

    pid = fork();

    if (pid == 0) /* Child process */
    {
        /* Redirect input and output if needed */
        if (input_fd != STDIN_FILENO)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        /* Find the full path of the command */
        full_path = find_full_path(command);
        if (full_path == NULL)
        {
            perror("Command not found");
            exit(1);
        }

        /* Execute the command */
        if (execve(full_path, args, NULL) == -1)
        {
            perror("execve");
            free(full_path);
            exit(1);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        /* Parent process waits for the child process to finish */
        wait(NULL);
    }
}

/* Function to execute pipe command */
void execute_pipe(char *command1, char *command2)
{
    pid_t pid1, pid2;
    int pipe_fd[2];
    char *args1[MAX_ARGS];
    char *args2[MAX_ARGS];
    int i;
    char *token;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return;
    }

    pid1 = fork();
    if (pid1 == 0) /* First child process */
    {
        close(pipe_fd[0]); /* Close the read end */
        dup2(pipe_fd[1], STDOUT_FILENO); /* Redirect stdout to pipe */
        close(pipe_fd[1]);

        /* Tokenize and build args for the first command */
        i = 0;
        token = strtok(command1, " ");
        while (token != NULL)
        {
            remove_quotes(token);
            args1[i++] = token;
            token = strtok(NULL, " ");
        }
        args1[i] = NULL;

        execute_command(args1[0], args1, STDIN_FILENO, pipe_fd[1]);
    }
    else if (pid1 < 0)
    {
        perror("fork");
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            close(pipe_fd[1]); /* Close the write end */
            dup2(pipe_fd[0], STDIN_FILENO); /* Redirect stdin from pipe */
            close(pipe_fd[0]);

            /* Tokenize and build args for the second command */
            i = 0;
            token = strtok(command2, " ");
            while (token != NULL)
            {
                remove_quotes(token);
                args2[i++] = token;
                token = strtok(NULL, " ");
            }
            args2[i] = NULL;

            execute_command(args2[0], args2, pipe_fd[0], STDOUT_FILENO);
        }
        else if (pid2 < 0)
        {
            perror("fork");
        }
        else
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}

/* Function to parse and execute commands */
void parse_and_execute(char *input)
{
    char *command1;
    char *command2;

    /* Get the first command */
    command1 = strtok(input, "|");

    while (command1 != NULL)
    {
        /* Check if there's a pipe and get the second command */
        command2 = strtok(NULL, "|");

        if (command2 != NULL)
        {
            execute_pipe(command1, command2);
        }
        else
        {
            char *args[MAX_ARGS];
            int i = 0;

            /* Tokenize the command and arguments */
            char *token = strtok(command1, " ");
            while (token != NULL)
            {
                remove_quotes(token);
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            execute_command(args[0], args, STDIN_FILENO, STDOUT_FILENO);
        }

        command1 = strtok(NULL, "|");
    }
}

int main()
{
    char input[MAX_COMMAND_LENGTH];

    while (1)
    {
        printf("simple_shell$ ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            exit(1);
        }

        /* Remove the trailing newline character */
        input[strcspn(input, "\n")] = 0;

        /* Exit the shell if the user types "exit" */
        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        /* Parse the input and execute the command(s) */
        parse_and_execute(input);
    }

    return (0);
}
