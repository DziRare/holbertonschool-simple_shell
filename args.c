#include <stdio.h>
#include <unistd.h>

/**
 * main - entry point of function
 */
int main(int ac, char **av)
{
	char *input;
	size_t size;

	input = NULL;
	size = 0;

	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}

	return (0);
}
