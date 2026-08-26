#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * execute_command - Run commands
 *
 * Return: Always 0
 */
int execute_command(char *command)
{
	pid_t child;
	int status;

	char *env_args[] = {"PATH=/bin/", NULL};
	char *argv[] = {NULL, NULL};

	argv[0] = command;
	
	child = fork();
	if (child == -1)
	{
		perror("Error");
		return (1);
	}

	if (child == 0)
	{
		if (execve(argv[0], argv, env_args) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
	else
	{
		wait(&status);
		/* Check STDOUT is a tty */
		if (isatty(STDIN_FILENO))
		{
			printf("( ͡° ͜ʖ ͡°)_/¯ ");
		}
	}

	return (0);
}
