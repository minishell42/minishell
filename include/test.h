#ifndef TEST_H
#define TEST_H

# include "minishell.h"

// char 	*get_err_msg(char *func_name, int case_number, char *expect, char *result);
// void	test_get_command_line(t_list *env);
// void	test_command_lines();
void	test_validate_line();
// void	test_redirection(t_list *env);
void	test_export();
void	test_env();
void 	test_unset();


void ft_lstdel_last(t_list *lst, void (*del)(void *));

// void	test_cd(t_list *env);


#endif