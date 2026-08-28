#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

char **split_string(int size, char *string);
char *read_line(void);
int execute_command(char *command);
char *path_handler(char *command);
int fork(void);

#endif /* _SIMPLE_SHELL_H_ */
