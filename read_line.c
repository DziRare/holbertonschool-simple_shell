#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 * read_line - Retrieves user input
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
		printf("( ͡° ͜ʖ ͡°)_/¯ ");
	}

	/* Prompt command from user */
    while ((read = getline(&buffer, &buffsize, stdin)) != -1)
	{
		/* Check STDOUT is a tty */
		if (isatty(STDIN_FILENO))
		{
			printf("( ͡° ͜ʖ ͡°)_/¯ ");
		}

		/* Remove newline if present */
		while (buffer[read-1] == '\n' || buffer[read-1] == ' ')
		{
			buffer[read - 1] = '\0';
			read--;
		}
		execute_command(buffer);
	}

	free(buffer);
	return (NULL);

    return(buffer);
}
