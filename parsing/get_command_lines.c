#include "parsing.h"

static bool	set_command(t_cmd_line *cmd_line, char *line, int *index, t_list *env)
{
	int			len;
	char		*start;
	static int	tmp_index = 0;

	start = line + *index;
	if (!check_character_in_line(line, index, ft_isspace))
		return (-1);
	len = (line + *index) - start;
	if (!line[*index + 1])
		len++;
	// 밖에서 에러 구조체 초기화 필요
	if (!parse_command(cmd_line, start, len, env))
	{
		*index = tmp_index;
		return (false);
	}
	while (line[*index] == ' ' && line[*index + 1] == ' ')
		(*index)++;
	(*index)++;
	tmp_index = *index;
	return (true);
}

static int	set_command_line(t_cmd_line *cmd_line, char *line, t_list *env)
{
	char			*start;
	int				len;
	int				index;
	int				tmp_index;
	
	index = 0;
	tmp_index = 0;
	while (line[index])
	{
		if (!set_command(cmd_line, line, &index, env))
		{
			if (g_err.err_number)
				return (-1);
			break;
		}
	}
	start = line + index;
	if ((tmp_index = set_param(cmd_line, start, env)) < 0)
		return (-1);
	index += tmp_index;
	return (index);
}

t_cmd_line	*get_command_line(char **line_ptr, t_list *env)
{	
	t_cmd_line		*command_line;
	int				index;
	char			*line;

	index = 0;
	while (ft_isspace((*line_ptr)[index]) && (*line_ptr)[index])
		index++;
	line = *line_ptr + index;
	if (!(command_line = ft_calloc(sizeof(t_cmd_line), 1)))
	{
		g_err.err_number = ALLOC_ERROR;
		return (NULL);
	}
	index = set_command_line(command_line, line, env);
	if (index < 0 || !check_redirection(command_line) || !change_param_value(command_line, env))
	{
		free_cmd_struct(command_line);
		free(command_line);
		return (NULL);
	}
	*line_ptr = line + index;
	return (command_line);
}

void	free_cmd_struct(t_cmd_line *cmd)
{
	t_list	*tmp;

	if (cmd->command)
		free(cmd->command);
	if (cmd->option)
		free(cmd->option);
	if (cmd->param != NULL)
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

t_list	*get_command_lines(char *line, t_list *env)
{
	t_list			*list;
	t_cmd_line		*command_line;

	list = NULL;
	g_err.err_number = 0;
	g_err.err_value = 0;
	while (line && *line)
	{
		printf("loop\n");
		if (!(command_line = get_command_line(&line, env)))
		{
			if (g_err.err_number)
				print_err_msg();
			break;
		}
		// flag -> pipe 있다는 것이고 -> 다음 command_line 이용해서 --- run 
		// res = run(command_line, res, env);
		// execve()
		// command_line.pipe_flag가 있으면 -> flag on
		if (!list)
			list = ft_lstnew(command_line);
		else
			ft_lstadd_back(&list, ft_lstnew(command_line));
	}
	return (list);
}