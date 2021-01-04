/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangpark <sangpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:44:02 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/03 05:44:11 by sangpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_env_list(t_list **env)
{
	t_list	*tmp;

	while (*env)
	{
		tmp = *env;
		free(tmp->content);
		*env = (*env)->next;
		free(tmp);
	}
}

void	free_redir_struct(void *redir_param)
{
	t_redir *redir;

	redir = (t_redir *)redir_param;
	if (redir->redir_flag)
		redir->redir_flag = 0;
	if (redir->redir_param)
		free(redir->redir_param);
	free(redir);
}

void	free_cmd_struct(t_cmd_line *cmd)
{
	if (cmd->command)
		free(cmd->command);
	if (cmd->option)
		free(cmd->option);
	if (cmd->param)
		ft_lstclear(&cmd->param, free);
	if (cmd->redir_param)
		ft_lstclear(&cmd->redir_param, free_redir_struct);
	free(cmd);
}
