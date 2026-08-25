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
	pid_t child_pid;
	int status;

	running = 1;
	while (running)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error: ");
			return (1);
		}

		/* Run shell via child process  */
		if (child_pid == 0)
		{
			/* Check STDOUT is a tty */
			if (isatty(STDIN_FILENO))
			{
				printf("( ͡° ͜ʖ ͡°)_/¯ ");
			}
			line = read_line();
			if (line == NULL || strcmp(line, "exit") == 0)
			{
				free(line);
				return (1);
			}
			execute_command(line);
			return (0);
		}
		else
		{
			wait(&status);

			/* Close shell if exit command is given  */
			if (status == 256)
			{
				if (isatty(STDIN_FILENO))
				{
					printf("Closing Shell!\n");
					printf("Goodbye!!\n");
				}
				return (0);
			}
		}
	}

	return (0);
}
