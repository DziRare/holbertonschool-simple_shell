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
	int running;

	running = 1;
	while (running)
	{
		line = read_line();
		if (line == NULL)
		{
			free(line);
			if (isatty(STDIN_FILENO))
			{
				printf("Closing Shell!\n");
				printf("Goodbye!!\n");
				return (0);
			}
			return (0);
		}
	
	}

	return (0);
}
