/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:16:02 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:16:04 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	argv_err(int argc, char **argv)
{
	if (argc != 1)
	{
		write(1, "error : ", 9);
		write(1, argv[0], ft_strlen(argv[0]));
		exit(1);
	}
}

static void	add_line(char **before_str, char *line)
{
	char		*tmp;

	if (*line)
	{
		if (!before_str)
			*before_str = ft_strdup(line);
		else
		{
			tmp = ft_strjoin(*before_str, line);
			free(*before_str);
			*before_str = tmp;
		}
	}
}

static char	*read_line(void)
{
	char		*line;
	char		*before_line;
	int			flag;

	before_line = NULL;
	flag = false;
	while (get_next_line(0, &line) <= 0)
	{
		if (*line || flag)
		{
			flag = true;
			add_line(&before_line, line);
		}
		else
			process_exit(1);
		free(line);
	}
	if (before_line)
	{
		add_line(&before_line, line);
		free(line);
		line = ft_strdup(before_line);
		free(before_line);
	}
	return (line);
}

int			main(int argc, char **argv, char *envp[])
{
	char		*line;

	argv_err(argc, argv);
	g_env = get_env_llist(envp);
	set_exit_status(EXIT_SUCCESS);
	while (true)
	{
		init_signal();
		prompt();
		line = read_line();
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		minishell(line);
		free(line);
	}
	if (g_env)
		free_env_list(&g_env);
	return (0);
}
