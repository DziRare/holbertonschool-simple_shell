#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **split_string(char *string);
int built_ins(char *line, int *status);
char *input_handler(void);
void trim(char *input);
int execute_command(char **args);
char *instruction_validator(char *instruction);
char *path_finder(void);
int fork(void);

extern char **environ;

#endif /* _SIMPLE_SHELL_H_ */
