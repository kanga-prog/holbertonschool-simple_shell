#include "shell.h"

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

	if (pid == 0)  /* Child process */
	{
		char *argv[2];

		argv[0] = command;
		argv[1] = NULL;

		if (execve(command, argv, NULL) == -1)
		{
			perror(command);  /* Print error if execve fails */
			_exit(1);  /* Exit child process after error */
		}
	}
	else  /* Parent process */
	{
		wait(NULL);  /* Wait for child process to finish */
	}
}
