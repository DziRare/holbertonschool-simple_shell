#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Run commands
 *
 * Return: Always 0
 */
int execute_command(char *command)
{
	pid_t grandchild;
	int status;

	char *env_args[] = {"PATH=/bin/", NULL};
	char *argv[] = {NULL, NULL};

	argv[0] = command;
	
	grandchild = fork();
	if (grandchild == -1)
	{
		perror("Error: ");
		return (1);
	}

	if (grandchild == 0)
	{
		if (execve(argv[0], argv, env_args) == -1)
		{
			perror("Error:");
		}
	}
	else
	{
		wait(&status);
	}

	return (0);
}
