#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
	while (i < size)
	{
		array[i] = token;
		token = strtok(NULL, " ");
		i = i + 1;
	}

	return array;
}
