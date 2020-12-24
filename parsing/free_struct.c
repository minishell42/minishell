#include "parsing.h"

void	free_env_list(t_list **env)
{
	t_list	*tmp;

	while (*env)
	{
		tmp = *env;
		free(tmp->content);
		*env = (*env)->next;
	}
}

// ------------------------ before ------------------------------------
// void	free_cmd_struct(t_cmd_line *cmd)
// {
// 	t_list	*tmp;

// 	if (cmd->command)
// 		free(cmd->command);
// 	if (cmd->option)
// 		free(cmd->option);
// 	if (cmd->param)
// 		free(cmd->param);
// 	while (cmd->redir_param)
// 	{
// 		tmp = cmd->redir_param;
// 		if (tmp->content)
// 			free(tmp->content);
// 		cmd->redir_param = cmd->redir_param->next;
// 		free(tmp);
// 	}
// }
// ------------------------ after ------------------------------------
// add free_redir_struct
void	free_redir_struct(t_redir *redir)
{
	if (redir->redir_flag)
		redir->redir_flag = 0;
	if (redir->redir_param)
		free(redir->redir_param);
}

void	free_cmd_struct(t_cmd_line *cmd)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_redir	*r;

	if (cmd->command)
		free(cmd->command);
	if (cmd->option)
		free(cmd->option);
	if (cmd->param)
		free(cmd->param);
	printf("free\n");
	tmp2 = cmd->redir_param;
	while (tmp2)
	{
		printf("while in\n");
		r = tmp2->content;
		if (r)
		{
			free_redir_struct(r);
			free(r);
		}
		tmp = tmp2;
		tmp2 = tmp2->next;
		free(tmp);
	}
}
