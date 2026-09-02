#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

/**
 * split_string - splits string into array
 * @string: string input
 * @size: size of array
 *
 * Return: array of string, NULL otherwise
 */
char **split_string(char *string)
{
	char **array;
	char *token;
	int i;
	int array_size;

	i = 0;
	array_size = 1;

	while (string[i] != '\0' && string != NULL)
	{
		if (string[i] == ' ')
		{
			array_size = array_size + 1;
		}
		i = i + 1;
	}
	array_size = array_size + 1;

	array = malloc(sizeof(string) * array_size);
	if (array == NULL)
	{
		free(string);
		return (NULL);
	}

	token = strtok(string, " ");
	i = 0;
	while (i < array_size - 1)
	{
		array[i] = token;
		token = strtok(NULL, " ");
		i = i + 1;
	}

	array[i] = NULL;

	return (array);
}

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

		args = split_string(line);
		args[0] = line_checker(args[0]);

		if (args[0] == NULL)
		{
			if (strchr(line, '/') == NULL)
				fprintf(stderr, "./hsh: 1: %s: command not found\n", line);
			else
				fprintf(stderr, "./hsh: 1: %s: No such file or directory\n", line);
			status = 127;
			free(line);
			free(args);
			continue;
		}
		execute_command(args);
		if (strchr(line, '/') == NULL)
			free(args[0]);
		free(line);
		free(args);
	}

	if (isatty(STDIN_FILENO))
		printf("exit\n");

	return (status);
}
