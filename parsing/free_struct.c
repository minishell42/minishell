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

void	free_cmd_struct(t_cmd_line *cmd)
{
	t_list	*tmp;

	if (cmd->command)
		free(cmd->command);
	if (cmd->option)
		free(cmd->option);
	if (cmd->param)
		free(cmd->param);
	while (cmd->redir_param)
	{
		tmp = cmd->redir_param;
		if (tmp->content)
			free(tmp->content);
		cmd->redir_param = cmd->redir_param->next;
		free(tmp);
	}
}
