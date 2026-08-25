#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Simple shell runs commands without any argument
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;

	line = read_line();
	execute_command(line);

	return (0);
}
