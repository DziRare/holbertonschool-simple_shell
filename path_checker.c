#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "main.h"

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
			if (token == NULL)
				return (NULL);
			path = malloc(sizeof(char) * (strlen(token) + 1));
			if (path == NULL || token == NULL)
			{
				free(env);
				return (NULL);
			}
			strcpy(path, token);
			free(env);
			break;
		}
		i = i + 1;
		free(env);
	}

	return (path);
}

/**
 * line_checker - validating input instruction/command
 * @instruction:  input instruction/command
 *
 * Return: executable string, NULL otherwise
 */
char *line_checker(char *instruction)
{
	char *path;
	char *token;
	char *full_path;
	struct stat st;

	if (strchr(instruction, '/') != NULL)
	{
		if (stat(instruction, &st) == 0)
		{
			return (instruction);
		}
		return (NULL);
	}

	path = path_finder();

	if (path == NULL)
		return (NULL);

	token = strtok(path, ":");
	while (token != NULL)
	{
		full_path = malloc(sizeof(char) * (strlen(token) + strlen(instruction) + 2));
		full_path[0] = '\0';
		strcat(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, instruction);

		if (stat(full_path, &st) == 0)
		{
			free(path);
			return (full_path);
		}
		token = strtok(NULL, ":");
		free(full_path);
		full_path = NULL;
	}
	free(path);
	return (NULL);
}
