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
  int input_file;
  int output_file;

  pid = fork();  /* Fork a new process */

  if (pid == 0)  /* Child process */
    {
      /* Handle input redirection */
      if (input_fd != STDIN_FILENO)
        {
          close(STDIN_FILENO);  /* Close standard input */
          input_file = open(command, O_RDONLY);
          if (input_file == -1)
            {
              perror("open input");
              exit(1);
            }
          /* Set input redirection */
          if (dup2(input_file, STDIN_FILENO) == -1)
            {
              perror("dup2 input");
              exit(1);
            }
          close(input_file);
        }

      /* Handle output redirection */
      if (output_fd != STDOUT_FILENO)
        {
          close(STDOUT_FILENO);  /* Close standard output */
          output_file = open(command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
          if (output_file == -1)
            {
              perror("open output");
              exit(1);
            }
          /* Set output redirection */
          if (dup2(output_file, STDOUT_FILENO) == -1)
            {
              perror("dup2 output");
              exit(1);
            }
          close(output_file);
        }

      /* Check if the command is an absolute path or a shell command */
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
          fprintf(stderr, "./shell: No such file or directory\n");
          exit(1);
        }
    }
  else if (pid < 0)  /* Error if fork fails */
    {
      perror("fork");
    }
  else  /* Parent process */
    {
      wait(NULL);  /* Wait for the child process to finish */
    }
}
