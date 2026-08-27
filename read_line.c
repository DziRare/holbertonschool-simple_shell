#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * trim - Remove whitespace from the start of string
 */
int trim(char *s) {

  	/* Two pointers initially at the beginning */
    int i = 0, j = 0;

    /* Skip leading spaces */
    while (s[i] == ' ') i++;

    /* iShift the characters of string to remove */
  	/* leading spaces */
    while ((s[j++] = s[i++]))
		;
	
	return(i-j);
}

/**
 * read_line - Retrieves user input
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
		return (NULL);
	}

	if (read == 0)
	{
		return ("");
	}

	trim_count = trim(buffer);

	/* Remove newline and trailing whitespace if present */
	while (buffer[read-1-trim_count] == '\n' || buffer[read-1-trim_count] == ' ')
	{
		buffer[read - 1 - trim_count] = '\0';
		read--;
	}

	return(buffer);
}
