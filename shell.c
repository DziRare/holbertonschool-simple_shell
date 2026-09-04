#include "main.h"
#include <signal.h>

/**
 * _atoi
 */
int _atoi(char *str)
{

	int number = 0;
	int i = 0;
	int digit;

	// Iterate through the string and add integers
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '-')
		{
			i++;
			continue;
		}

		digit = str[i] - '0';
		if (digit < 0 || digit > 9)
		{
			printf("./hsh: exit: %s: numeric arguent required\n", str);
			return (-1); 
		}

		number = number * 10 + digit;
		i++;
	}

	if (str[0] == '-')
		number = number * -1;	

	return number;
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
	int i;
	char *exit_code;

	if (strcmp(strtok(line, " "), "exit") == 0)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("exit\n");
		}
		if ((exit_code = strtok(NULL, " ")) != NULL)
		{
			*status = _atoi(exit_code);
			if (*status == -1)
			{
				*status = 2;
				return (TRUE);
			}
		}

		free(line);
		exit(*status);
	}
	else if (strcmp(line, "env") == 0)
	{
		i = 0;
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i = i + 1;
		}
		*status = 0;
		free(line);
		return (TRUE);
	}

	return (FALSE);
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
	signal(SIGINT, SIG_IGN);

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
