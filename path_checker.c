#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * path_checker - Checks the command against the PATH
 *
 * Return: Full executable path
 */
char *path_checker(char *command)
{
    unsigned int i;
	extern char **environ;
	char *token;
	char *path;
	char *full_path;
	struct stat st;
	char *env;

	if (command[0] == '/')
	{
		if (stat(command, &st) == 0)
		{
			return (command);
		}
	}

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
    }

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
			free(env);
			return (full_path);
		}

		token = strtok(NULL, ":");
		free(full_path);
	}
	free(env);
    return (NULL);
}
