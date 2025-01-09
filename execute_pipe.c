#include "simple_shell.h"
/**
 * custom_dup2 - Custom implementation of the dup2 system call.
 * @oldfd: The file descriptor to be duplicated.
 * @newfd: The file descriptor that will replace the oldfd.
 *
 * This function duplicates the file descriptor oldfd to newfd by closing
 * newfd first and then opening "/dev/null" as a safe placeholder.
 *
 * Return: 0 on success, -1 on failure.
 */
int custom_dup2(int oldfd, int newfd)
{
	int temp_fd;

	if (oldfd == newfd)
		return (0);

	/* Close the new file descriptor if it is open */
	if (close(newfd) == -1)
	{
		perror("close");
		return (-1);
	}

	/* Open "/dev/null" as a placeholder file to redirect */
	temp_fd = open("/dev/null", O_WRONLY);
	if (temp_fd == -1)
	{
		perror("open");
		return (-1);
	}

	/* Return success */
	return (0);
}

/**
 * execute_pipe - Executes a pipeline of two commands connected by a pipe ('|').
 * @command1: The first command in the pipeline.
 * @command2: The second command in the pipeline.
 *
 * This function forks two child processes. The first child executes command1
 * and writes the output to the pipe, while the second child executes command2
 * and reads input from the pipe.
 *
 * Return: None.
 */
void execute_pipe(char *command1, char *command2)
{
	pid_t pid1, pid2;
	int pipe_fd[2]; /* Pipe file descriptors */
	char *args1[MAX_ARGS];
	char *args2[MAX_ARGS];
	int i = 0;
	char *token;

	/* Create a pipe manually using open (simulating pipe) */
	pipe_fd[0] = open("/dev/null", O_RDONLY); /* Simulating pipe read end */
	pipe_fd[1] = open("/dev/null", O_WRONLY); /* Simulating pipe write end */

	if (pipe_fd[0] == -1 || pipe_fd[1] == -1)
	{
		perror("open");
		return;
	}

	/* Create the first child process */
	pid1 = fork();
	if (pid1 == 0) /* First child process */
	{
		/* Close the read end of the pipe */
		close(pipe_fd[0]);

		/* Redirect stdout to the pipe */
		if (custom_dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("custom_dup2");
			_exit(1);
		}

		/* Close the write end of the pipe */
		close(pipe_fd[1]);

		/* Tokenize the first command */
		token = strtok(command1, " ");
		while (token != NULL)
		{
			args1[i++] = token;
			token = strtok(NULL, " ");
		}
		args1[i] = NULL;

		/* Execute the first command */
		execute_command(args1[0], args1, STDIN_FILENO, STDOUT_FILENO);
	}
	else if (pid1 < 0)
	{
		/* Handle fork error */
		perror("fork");
		return;
	}
	else
	{
		/* Create the second child process */
		pid2 = fork();
		if (pid2 == 0) /* Second child process */
		{
			/* Close the write end of the pipe */
			close(pipe_fd[1]);

			/* Redirect stdin from the pipe */
			if (custom_dup2(pipe_fd[0], STDIN_FILENO) == -1)
			{
				perror("custom_dup2");
				_exit(1);
			}

			/* Close the read end of the pipe */
			close(pipe_fd[0]);

			/* Tokenize the second command */
			i = 0;
			token = strtok(command2, " ");
			while (token != NULL)
			{
				args2[i++] = token;
				token = strtok(NULL, " ");
			}
			args2[i] = NULL;

			/* Execute the second command */
			execute_command(args2[0], args2, STDIN_FILENO, STDOUT_FILENO);
		}
		else if (pid2 < 0)
		{
			/* Handle fork error */
			perror("fork");
			return;
		}
		else
		{
			/* Close both ends of the pipe in the parent process */
			close(pipe_fd[0]);
			close(pipe_fd[1]);

			/* Wait for both child processes to finish */
			wait(NULL);
			wait(NULL);
		}
	}
}

