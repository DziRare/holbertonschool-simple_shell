#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

/**
 * main - Simple shell runs commands without any argument
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	int status;
	int i;
	extern char **environ;
	
	signal(SIGINT, SIG_IGN);

	status = 0;

	while ((line = read_line()) != NULL)
	{
		if (strcmp(line, "") == 0)
		{
			continue;
		}
		i = 0;
		if (strcmp(line, "exit") == 0)
		{
			if (isatty(STDIN_FILENO))
			{
				printf("exit\n");
			}

			free(line);
			return (status);
		}
		else if (strcmp(line, "env") == 0) 
		{
			while (environ[i] != NULL)
			{
				printf("%s\n", environ[i]);
				i = i + 1;
			}
			status = 0;
			free(line);
			continue;
		}
		status = execute_command(strtok(line, "\0"));
		free(line);
	}

	if (isatty(STDIN_FILENO))
	{
		printf("exit\n");
	}

	free(line);
	return (status);
}
