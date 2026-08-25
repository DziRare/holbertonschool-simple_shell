#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * main - executes the command ls -l /tmp in 5 different child processes
 *
 * Return: Always 0
 */
int main(void)
{
	pid_t my_pid;
	pid_t parent_pid;
	pid_t child_pid;
	int status;
	int i;

	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	char *env_args[] = {"PATH=/bin/", NULL};

	i = 0;
	while (i < 5)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			my_pid = getpid();
			parent_pid = getppid();
			printf("Parent: %u\n", parent_pid);
			printf("Child: %u\n", my_pid);
			if (execve(argv[0], argv, env_args) == -1)
			{
				perror("Error:");
			}
		}
		else
		{
			wait(&status);
			printf("Done\n\n");
		}
		i = i + 1;
	}
	return (0);
}
