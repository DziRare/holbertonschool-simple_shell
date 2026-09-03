#include "main.h"
#include <sys/wait.h>
#include <errno.h>

/**
 * execute_command - Run executable file
 * @args: Array containing executable file and arguemnts
 *
 * Return: status
 */
int execute_command(char **args)
{
	pid_t child;
	int status;
	int exit_status;

	status = 0;

	child = fork();
	if (child == -1)
	{
		perror("Error");
		return (status);
	}

	if (child == 0)
	{
		execve(args[0], args, environ);
		perror("Error");
		exit(status);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (status);
}
