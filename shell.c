#include "main.h"
#include <signal.h>

/**
 * _atoi - Turns ASCII value into an integer value
 * @str: Array of ascii characters to convert into integers
 *
 * Return: The converted integer value (exit code) on success,
 * otherwise -1 on failure
 */
int _atoi(char *str)
{

	int number = 0;
	int i = 0;
	int digit;

	while (str[i] != '\0')
	{
		digit = str[i] - '0';
		if (digit < 0 || digit > 9)
		{
			fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", str);
			return (-1);
		}

		number = number * 10 + digit;
		i++;
	}

	return (number);
}

/**
 * _get_env - prints all the environment functions
 *
 * Return: 0 for success
 */
int _get_env(void)
{
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i = i + 1;
	}
	return (0);
}

/**
 * built_ins - checks if input is a built-in command and executes
 * @line: input string
 * @status: last status code
 *
 * Return: status code
 */
int built_ins(char *line, int *status)
{
	char *exit_code;
	char *line_copy;

	line_copy = malloc(sizeof(char) * (strlen(line) + 1));
	strcpy(line_copy, line);

	if (strcmp(strtok(line_copy, " "), "exit") == 0)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");

		exit_code = strtok(NULL, " ");
		if (exit_code != NULL)
		{
			*status = _atoi(exit_code);
			if (*status == -1)
			{
				*status = 2;
				free(line_copy);
				free(line);
				return (TRUE);
			}
		}

		free(line_copy);
		free(line);
		exit(*status);
	}
	else if (strcmp(line, "env") == 0)
	{
		*status = _get_env();
		free(line_copy);
		free(line);
		return (TRUE);
	}

	free(line_copy);
	return (FALSE);
}

/**
 * sigint_handler - handles signal interrupt (Ctrl + C)
 * @signal: signal that is received
 */
void sigint_handler(int signal)
{
	(void) signal;
	printf("\n╚( ⚆ ⌂ ☉)╝ ");
	fflush(stdout);
}

/**
 * main - Simple shell runs commands with arguments
 *
 * Return: 0 on success, otherwise last status code
 */
int main(void)
{
	char *line;
	int status;
	char **args;

	status = 0;
	signal(SIGINT, sigint_handler);

	while ((line = input_handler()) != NULL)
	{
		if (strcmp(line, "") == 0)
			continue;

		if (built_ins(line, &status))
			continue;

		args = split_string(line);
		args[0] = instruction_validator(args[0]);

		if (args[0] == NULL)
		{
			if (strchr(line, '/') == NULL)
				fprintf(stderr, "./hsh: 1: %s: not found\n", line);
			else
				fprintf(stderr, "./hsh: 1: %s: No such file or directory\n", line);
			status = 127;
			free(line);
			free(args);
			continue;
		}
		status = execute_command(args);
		if (strchr(line, '/') == NULL)
			free(args[0]);
		free(line);
		free(args);
	}

	if (isatty(STDIN_FILENO))
		printf("exit\n");

	return (status);
}
