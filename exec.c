#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * execute_command - Run commands
 * @args: Array containing command, path and arguemnts
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
		if (execve(args[0], args, environ) == -1)
		{
			perror("Error");
			return (status);
		}
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
