#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "main.h"

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
		env = malloc(sizeof(char) * (strlen(environ[i]) + 1));
		strcpy(env, environ[i]);
		token = strtok(env, "=");
		if (strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			path = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(path, token);
			free(env);
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
 * line_checker - Transforms input string to array for execve
 * @input: Input string from read_line
 *
 * Return: array or args for execve, NULL otherwise
 */
char **line_checker(char *input)
{
	char *path;
	char *token;
	char **args;
	char *full_path;
	char *command;
	struct stat st;

	args = split_string(input);
	command = args[0];

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
		{
			args[0] = malloc(strlen(command) + 1);
			if (args[0] == NULL)
			{
				free(args);
				return (NULL);
			}
			strcpy(args[0], command);
			return (args);
		}
		return (NULL);
	}

	path = path_finder();
	token = strtok(path, ":");
	while (token != NULL)
	{
		full_path = malloc(sizeof(char) * (strlen(token) + strlen(command) + 2));
		full_path[0] = '\0';
		strcat(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0)
		{
			args[0] = full_path;
			free(path);
			return (args);
		}
		token = strtok(NULL, ":");
		free(full_path);
		full_path = NULL;
	}
	free(path);
	free(args);
	return (NULL);
}
