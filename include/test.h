#ifndef TEST_H
#define TEST_H

# include "../minishell.h"

char 	*get_err_msg(char *func_name, int case_number, char *expect, char *result);
void	test_get_command_line(void);

#endif