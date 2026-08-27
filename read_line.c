#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>

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
		/* Remove newline and trailing whitespace if present */
		while (buffer[read-1] == '\n' || buffer[read-1] == ' ')
		{
			buffer[read - 1] = '\0';
			read--;
		}
		/* Check EOF and exit condition */
		if (buffer == NULL || strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			return (NULL);
		}
		
		execute_command(buffer);
	}
	free(buffer);
    return(NULL);
}
