#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * execute_command - Run commands
 * @command: Command that user is attempting to run
 * Return: status
 */
int execute_command(char **args)
{
	pid_t child;
	char *full_path;
	int status;
	int exit_status;
	char *env[] = {"PATH=/bin/", NULL};

	full_path = args[0];
	status = 0;

	child = fork();
	if (child == -1)
	{
		free(args);
		perror("Error");
		return (status);
	}

	if (child == 0)
	{
		if (execve(full_path, args, env) == -1)
		{
			printf("%s\n", full_path);
			perror("Error");
			free(args[0]);
			free(args);
			return (status);
		}
	}
	else
	{
		if (strchr(args[0], '/') == NULL)
			free(full_path);
		free(args);
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (status);
}
