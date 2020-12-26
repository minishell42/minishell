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
	tmp2 = cmd->redir_param;
	while (tmp2)
	{
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
