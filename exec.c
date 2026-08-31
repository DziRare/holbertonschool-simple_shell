#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * array_size - finds the size of the array
 * @input: input string
 *
 * Return: size of array
 */
int array_size(char *input)
{
	int size;
	int i;

	i = 0;
	size = 1;

	while (input[i] != '\0' && input != NULL)
	{
		if (input[i] == ' ')
		{
			size = size + 1;
		}
		i = i + 1;
	}
	size = size + 1;

	return (size);
}

/**
 * split_string - splits string into array
 * @string: string input
 * @size: size of array
 *
 * Return: array of string, NULL otherwise
 */
char **split_string(int size, char *string)
{
	char **array;
	char *token;
	int i;

	array = malloc(sizeof(string) * size);
	if (array == NULL || size == 0)
	{
		return (NULL);
	}

	token = strtok(string, " ");
	i = 0;
	while (i < size - 1)
	{
		array[i] = token;
		token = strtok(NULL, " ");
		i = i + 1;
	}
	array[i] = NULL;

	return (array);
}

/**
 * execute_command - Run commands
 * @command: Command that user is attempting to run
 * Return: status
 */
int execute_command(char *command)
{
	pid_t child;
	int status;
	int exit_status;
	int size;
	char **input;
	char *full_path;
	char *env[] = {"PATH=/bin/", NULL};

	full_path = NULL;
	status = 0;
	size = array_size(command);
	input = split_string(size, command);
	full_path = path_checker(input[0]);

	if (full_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", input[0]);
		free(input);
		return (127);
	}
	child = fork();
	if (child == -1)
	{
		free(input);
		perror("Error");
		return (status);
	}

	if (child == 0)
	{
		if (execve(full_path, input, env) == -1)
		{
			printf("%s\n", full_path);
			perror("Error");
			free(command);
			free(input);
			return (status);
		}
	}
	else
	{
		if (strchr(input[0], '/') == NULL)
			free(full_path);
		free(input);
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (status);
}
