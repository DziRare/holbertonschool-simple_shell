#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * trim - Remove whitespace from the start of string
 * @s: String to be trimmed
 *
 * Return: Amount of space removed from string
 */
int trim(char *s)
{

	/* Two pointers initially at the beginning */
	int i = 0, j = 0;

	/* Skip leading spaces */
	while (s[i] == ' ')
		i++;

	/* iShift the characters of string to remove */
	/* leading spaces */
	while ((s[j++] = s[i++]))
		;

	return (i - j);
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
	int trim_count;

	buffsize = 0;
	buffer = NULL;
	trim_count = 0;

	/* Check STDOUT is a tty */
	if (isatty(STDIN_FILENO))
	{
		printf("( ͡° ͜ʖ ͡°)_/¯ ");
	}

	/* Prompt command from user */
	read = getline(&buffer, &buffsize, stdin);
	if (read == -1)
	{
		free(buffer);
		return (NULL);
	}

	trim_count = trim(buffer) + 1;

	if (read == 0 || buffer[0] == '\0' || buffer[0] == '\n')
	{
		free(buffer);
		return ("");
	}

	/* Remove newline and trailing whitespace if present */
	while (buffer[read - trim_count] == '\n' || buffer[read - trim_count] == ' ')
	{
		buffer[read - trim_count] = '\0';
		read--;
	}

	return (buffer);
}
