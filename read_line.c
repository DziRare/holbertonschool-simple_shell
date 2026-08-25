#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * read_line - Retrieves user input
 */
char *read_line(void)
{
    char *buffer;
    size_t buffsize;
	ssize_t read;

	//Prompt command from user
    printf("( ͡° ͜ʖ ͡°)_/¯ ");
    read = getline(&buffer, &buffsize, stdin);

	//Remove newline if present
	if (read != -1) {
        if (buffer[read - 1] == '\n') {
            buffer[read - 1] = '\0';
            read--;
        }
    }

	//Debugging: Check what's being added to the buffer
    printf("%s\n", buffer);

    return(buffer);
}
