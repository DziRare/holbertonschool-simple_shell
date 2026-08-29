#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_string - splits string into array
 * @string - string input
 * @size - size of array
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

    return array;
}

/**
 * execute_command - Run commands
 *
 * Return: Always 0
 */
int execute_command(char *command)
{
	pid_t child;
	int status;
	int i;
	int size;
	char **input;
	char *full_path;
	char *env[] = {"PATH=/bin/", NULL};

	i = 0;
	size = 1;
	full_path = NULL;

	while (command[i] != '\0' && command != NULL)
	{
		if (command[i] == ' ')
		{
			size = size + 1;
		}
		i = i + 1;
	}
	size = size + 1;

	input = split_string(size, command);	
	
	full_path = path_checker(input[0]);

	if (full_path == NULL)
	{
		if (strchr(input[0], '/') == NULL)
			fprintf(stderr, "./hsh: 1: %s: not found\n", input[0]);
		free(input);
		return (0);
	}

	child = fork();
	if (child == -1)
	{
		free(input);
		perror("Error");
		return (1);
	}

	if (child == 0)
	{
		if (execve(full_path, input, env) == -1)
		{
			perror("Error");
			free(command);
			free(input);
			exit(1);
		}
	}
	else
	{
		if (strchr(input[0], '/') == NULL)
			free(full_path);
		free(input);
		wait(&status);
	}

	return (0);
}
