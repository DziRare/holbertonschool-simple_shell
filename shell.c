#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

/**
 * _get_env - print all environment variables
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

	status = 0;
	signal(SIGINT, SIG_IGN);

	while ((line = read_line()) != NULL)
	{
		if (strcmp(line, "") == 0)
			continue;
		
		if (built_ins(line, &status))
			continue;
		printf("Executing Command!\n");
		status = execute_command(strtok(line, "\0"));
		free(line);
	}

	if (isatty(STDIN_FILENO))
		printf("exit\n");

	free(line);
	return (status);
}
