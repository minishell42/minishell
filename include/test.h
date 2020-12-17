#ifndef TEST_H
#define TEST_H

# include "minishell.h"

char 	*get_err_msg(char *func_name, int case_number, char *expect, char *result);
void	test_get_command_line(t_list *env);
void	test_command_lines(t_list *env);
void	test_validate_line();
void	test_redirection(t_list *env);
void	test_export(t_list *env);

#endif