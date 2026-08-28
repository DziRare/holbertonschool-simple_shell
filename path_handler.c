#include <stdio.h> 
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>

/**
 * path_handler - Handles PATH if command is entered
 *
 * Return: Full path of command
 */
char *path_handler(char *command)
{
    struct stat st;
	char *path;
	char *executable;

	path = "/bin/";
	executable = malloc(sizeof(char) * (strlen(path) + strlen(command)) + 1);

	executable[0] = '\0';
	strcat(executable, path);
	strcat(executable, command);

	if (stat(executable, &st) == 0)
	{
		return (executable);
	}
	else
	{
		free(executable);
		printf("hsh: command not found: %s\n", command);
		return (NULL);
	}
}
