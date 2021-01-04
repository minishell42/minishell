/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 04:44:11 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/04 15:01:43 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	set_redir_flag(t_redir *redir, char *param, char **content)
{
	if (**content == '>')
	{
		redir->redir_flag = OUT_OVERRIDE;
		(*content)++;
		if (**content == '>')
		{
			(*content)++;
			redir->redir_flag = OUT_ENDLINE;
		}
	}
	else if (**content == '<')
	{
		(*content)++;
		redir->redir_flag = REDIR_IN;
	}
	while (ft_isspace(**content))
		(*content)++;
	if (**content == '\0')
		return (false);
	return (true);
}

static bool	set_other_param(t_cmd_line *cmd_line, \
						char *content, int index)
{
	char	*other_param;
	t_list	*other_param_list;
	t_list	*tmp;

	if (!(other_param = \
			ft_substr(content, index, ft_strlen(content) - index)))
		return (false);
	other_param_list = make_param_list(other_param);
	if ((!cmd_line->command || !*cmd_line->command) && other_param_list)
	{
		free(cmd_line->command);
		cmd_line->command = (char *)other_param_list->content;
		tmp = other_param_list;
		other_param_list = other_param_list->next;
		free(tmp);
	}
	if (!cmd_line->param)
		cmd_line->param = other_param_list;
	else if (other_param_list)
		ft_lstadd_back(&cmd_line->param, other_param_list);
	free(other_param);
	return (true);
}

static bool	set_redir_param(t_cmd_line *cmd_line, \
						t_redir *redir, char *content)
{
	int		index;
	char	*tmp;
	char	*file_name;
	char	*file;

	index = 0;
	if (content[index] && \
			check_character_in_line(content, &index, ft_isspace))
		tmp = ft_substr(content, 0, index);
	if (!(file_name = convert_to_valid_value(tmp, ft_strlen(tmp))))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	if (file = change_to_absolute_path(file_name))
	{
		redir->redir_param = file;
		free(file_name);
	}
	else
		redir->redir_param = file_name;
	if (!set_other_param(cmd_line, content, index))
		return (false);
	return (true);
}

bool		can_make_redir_list(t_cmd_line *cmd_line, \
							char *param, char *content)
{
	t_redir		*redir;
	t_list		*list;
	char		*tmp;

	list = cmd_line->redir_param;
	tmp = content;
	if (!(redir = ft_calloc(sizeof(t_redir), 1)))
		return (false);
	if (!(set_redir_flag(redir, param, &tmp)))
	{
		free(redir);
		return (false);
	}
	if (!(set_redir_param(cmd_line, redir, tmp)))
	{
		free(redir);
		return (false);
	}
	ft_lstadd_back(&list, ft_lstnew(redir));
	cmd_line->redir_param = list;
	return (true);
}
