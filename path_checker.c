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
char *path_checker(char *command)
{
	char *path;
	char *full_path;
	struct stat st;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
		{
			return (command);
		}
		else
		{
			return (NULL);
		}
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
			return (full_path);
		}

		path = strtok(NULL, ":");
		free(full_path);
	}

	return (NULL);
}
