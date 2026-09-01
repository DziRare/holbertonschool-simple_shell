#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

/**
 * built_ins - checks and executes command if built
 * @line: input string
 * @status: exit status
 *
 * Return: status code
 */
int built_ins(char *line, int *status)
{
	int i;

	if (strcmp(line, "exit") == 0)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("exit\n");
		}

		free(line);
		exit(*status);
	}
	else if (strcmp(line, "env") == 0)
	{
		i = 0;
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i = i + 1;
		}
		*status = 0;
		free(line);
		return (TRUE);
	}

	return (FALSE);
}

/**
 * main - Simple shell runs commands without any argument
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	int status;
	char **args;

	status = 0;
	signal(SIGINT, SIG_IGN);

	while ((line = read_line()) != NULL)
	{
		if (strcmp(line, "") == 0)
			continue;

		if (built_ins(line, &status))
			continue;

		args = path_checker(line);
		if (args == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", line);
			status = 127;
			free(line);
			continue;
		}
		if (args[0] == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			free(args[0]);
			free(args);
			free(line);
			status = 127;
			continue;
		}

		execute_command(args);
	}

	if (isatty(STDIN_FILENO))
		printf("exit\n");

	free(line);
	return (status);
}
