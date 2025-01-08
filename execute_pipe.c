#include "simple_shell.h"
/**
 * execute_pipe - Executes a command pipeline (two commands connected by '|').
 * @command1: The first command in the pipeline.
 * @command2: The second command in the pipeline.
 */
void execute_pipe(char *command1, char *command2)
{
	pid_t pid1, pid2;
	int pipe_fd[2];
	char *args1[MAX_ARGS];
	char *args2[MAX_ARGS];
	int i = 0;
	char *token;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return;
	}
	pid1 = fork(); /* Fork the first child process */
	if (pid1 == 0) /* First child process */
	{
		close(pipe_fd[0]); /* Close the read end */
		dup2(pipe_fd[1], STDOUT_FILENO); /* Redirect stdout to the pipe */
		close(pipe_fd[1]);
		token = strtok(command1, " ");
		while (token != NULL)
		{
			remove_quotes(token);  /* Remove quotes around the argument */
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
		pid2 = fork(); /* Fork the second child process */
		if (pid2 == 0) /* Second child process */
		{
			close(pipe_fd[1]); /* Close the write end */
			dup2(pipe_fd[0], STDIN_FILENO); /* Redirect stdin from the pipe */
			close(pipe_fd[0]);
			i = 0;
			token = strtok(command2, " ");
			while (token != NULL)
			{
				remove_quotes(token);  /* Remove quotes around the argument */
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
			wait(NULL); /* Wait for both child processes to finish */
			wait(NULL);
		}
	}
}
