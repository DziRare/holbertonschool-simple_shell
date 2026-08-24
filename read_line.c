#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - entry point of function
 */
int main(void)
{
    char *buffer;
    size_t buffsize = 32;

    buffer = malloc(buffsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
		exit(1);
    }

    printf("$ ");
    getline(&buffer, &buffsize, stdin);
    printf("%s", buffer);

    return(0);
}
