#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * trim - Remove whitespace from the start of string
 * @input: String to be trimmed
 */
void trim(char *input)
{
	int i;
	int j;
	int input_len;

	i = 0;
	j = 0;
	input_len = strlen(input);

	/* Skip leading spaces */
	while (input[i] == ' ')
	{
		i = i + 1;
	}

	/* Shifting characters of string to remove leading spaces*/
	while (i < input_len + 1)
	{
		input[j] = input[i];
		j = j + 1;
		i = i + 1;
	}

	j = j - 2;

	/* Remove newline and trailing whitespace if present */
	while (input[j] == '\n' || input[j] == ' ')
	{
		input[j] = '\0';
		j--;
	}
}

/**
 * read_line - Retrieves user input
 *
 * Return: The command and it's arguments or NULL on failure
 */
char *read_line(void)
{
	char *buffer;
	size_t buffsize;
	ssize_t read;

	buffsize = 0;
	buffer = NULL;

	/* Check STDOUT is a tty */
	if (isatty(STDIN_FILENO))
	{
		printf("╚( ⚆ ⌂ ☉)╝ ");
	}

	/* Prompt command from user */
	read = getline(&buffer, &buffsize, stdin);
	printf("Size: %ld\n", read);

	/* Check input if EOF */
	if (read == -1 || read == 1)
	{
		free(buffer);
		return (NULL);
	}

	trim(buffer);

	/* Check input if only white space */
	if (buffer[0] == '\0' || buffer[0] == '\n')
	{
		free(buffer);
		return ("");
	}

	return (buffer);
}
