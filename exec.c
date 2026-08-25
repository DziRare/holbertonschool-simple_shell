#include "main.h"
#include <stdio.h>
#include <unistd.h>

/**
 * execute_command - Run commands
 *
 * Return: Always 0
 */
int execute_command(char *command)
{
	char *env_args[] = {"PATH=/bin/", NULL};
	char *argv[] = {NULL, NULL};

	argv[0] = command;
	if (execve(argv[0], argv, env_args) == -1)
	{
		perror("Error:");
	}
	return (0);
}
