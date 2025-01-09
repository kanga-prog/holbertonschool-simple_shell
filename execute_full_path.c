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
void execute_command(char *command, char *args[], int input_fd, int output_fd)
{
	pid_t pid;

	pid = fork();

	if (pid == 0) /* Child process */
	{
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
		if (command[0] == '/')
		{
			if (execve(command, args, NULL) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
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
		wait(NULL);
	}
}
