#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Simple shell runs commands without any argument
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	
	while ((line = read_line()) != NULL)
	{
		if (strcmp(line, "") == 0)
		{
			continue;
		}
		if (strcmp(line, "exit") == 0)
		{
			if (isatty(STDIN_FILENO))
			{
				printf("exit\n");
			}

			free(line);
			return (0);
		}
		execute_command(strtok(line, "\0"));
		free(line);
	}

	if (isatty(STDIN_FILENO))
	{
		printf("exit\n");
	}

	free(line);
	return (0);
}
