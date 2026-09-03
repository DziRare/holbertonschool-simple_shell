#include "main.h"

/**
 * split_string - splits input string into args array
 * @string: string input
 *
 * Return: array of strings, NULL otherwise
 */
char **split_string(char *string)
{
	char **array;
	char *token;
	int i;
	int array_size;

	i = 0;
	array_size = 1;

	while (string[i] != '\0' && string != NULL)
	{
		if (string[i] == ' ')
		{
			array_size = array_size + 1;
		}
		i = i + 1;
	}
	array_size = array_size + 1;

	array = malloc(sizeof(string) * array_size);
	if (array == NULL)
	{
		free(string);
		return (NULL);
	}

	token = strtok(string, " ");
	i = 0;
	while (i < array_size - 1)
	{
		array[i] = token;
		token = strtok(NULL, " ");
		i = i + 1;
	}

	array[i] = NULL;

	return (array);
}

/**
 * trim - Remove whitespace from the start of string
 * @input: String to be trimmed
 */
void trim(char *input)
{
	size_t i;
	int j;
	size_t input_len;

	i = 0;
	j = 0;
	input_len = strlen(input);

	/* Skip leading spaces */
	while (input[i] == ' ')
	{
		i = i + 1;
	}

	if (input_len == i + 1)
	{
		input[0] = '\0';
		return;
	}

	/* Shifting characters of string to remove leading spaces*/
	while (i < input_len + 1)
	{
		input[j] = input[i];
		j = j + 1;
		i = i + 1;
	}

	j = j - 2;

	/* Remove newline and trailing whitespace if present */
	while (input[j] == '\n' || input[j] == ' ')
	{
		input[j] = '\0';
		j--;
	}
}

/**
 * read_line - Retrieves user input
 *
 * Return: The command and it's arguments or NULL on failure
 */
char *input_handler(void)
{
	char *buffer;
	size_t buffsize;
	ssize_t read;

	buffsize = 0;
	buffer = NULL;

	/* Check STDOUT is a tty */
	if (isatty(STDIN_FILENO))
	{
		printf("╚( ⚆ ⌂ ☉)╝ ");
	}

	/* Prompt command from user */
	read = getline(&buffer, &buffsize, stdin);

	/* Check input if EOF */
	if (read == -1)
	{
		free(buffer);
		return (NULL);
	}

	if (read == 1)
	{
		free(buffer);
		return ("");
	}

	trim(buffer);

	/* Check input if only white space */
	if (buffer[0] == '\0' || buffer[0] == '\n')
	{
		free(buffer);
		return ("");
	}

	return (buffer);
}
