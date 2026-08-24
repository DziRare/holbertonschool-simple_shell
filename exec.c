#include "main.h"
#include <stdio.h>
#include <unistd.h>

/**
 * main - execve
 *
 * Return: Always 0
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};
	char *env_args[] = {"PATH=/bin/", NULL};

	printf("Before execve\n");
	if (execve(argv[0], argv, env_args) == -1)
	{
		perror("Error:");
	}
	printf("After execve\n");
	return (0);
}
