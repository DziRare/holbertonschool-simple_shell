#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#define TRUE 1
#define FALSE 0

char **split_string(char *string);
char *read_line(void);
int execute_command(char **args);
char **line_checker(char *input);
int fork(void);

extern char **environ;

#endif /* _SIMPLE_SHELL_H_ */
