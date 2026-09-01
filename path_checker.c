#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "main.h"

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
 * path_finder - find path in env variables
 *
 * Return: path if found, NULL otherwise
 */
char *path_finder(void)
{
	int i;
	char *path;
	char *env;
	char *token;

	i = 0;
	path = NULL;

	while (environ[i] != NULL)
	{
		env = malloc(sizeof(char) * strlen(environ[i]) + 1);
		strcpy(env, environ[i]);
		token = strtok(env, "=");
		if (strcmp(token, "PATH") == 0)
		{
			path = strtok(NULL, "=");
			break;
		}
		i++;
		free(env);
		env = NULL;
	}

	if (path == NULL)
	{
		free(env);
		return (NULL);
	}

	return (path);
}

/**
 * path_checker - Checks the command against the PATH
 * @command: Instruction user is attempting to perform
 *
 * Return: Full executable path
 */
char **path_checker(char *input)
{
	char *path;
	char **args;
	char *full_path;
	char *command;
	int size;
	struct stat st;

	size = array_size(input);
	args = split_string(size, input);
	command = args[0];

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (args);
		else
			return (NULL);
	}

	path = path_finder();
	path = strtok(path, ":");
	while (path != NULL)
	{
		full_path = malloc(sizeof(char) * (strlen(path) + strlen(command) + 2));
		full_path[0] = '\0';
		strcat(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0)
		{
			args[0] = full_path;
			return (args);
		}
		path = strtok(NULL, ":");
		free(full_path);
	}

	return (NULL);
}
