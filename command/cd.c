/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:00:12 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:00:16 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static bool	set_chdir(t_cmd_line *cmd_line, char *dir, bool flag)
{
	if (flag)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	if (cmd_line->pipe_flag)
		return (false);
	if (chdir(dir) < 0)
	{
		make_err_msg(EXIT_FAILURE, "cd", dir,
					get_err_msg(NO_FILE_OR_DIRECTORY));
		return (false);
	}
	return (true);
}

static bool	set_pwd_to_env(char *env_value)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
		return (false);
	set_env_target(env_value, pwd);
	free(pwd);
	return (true);
}

static bool	set_cd(t_cmd_line *cmd_line, char *dir, bool flag)
{
	char		*old_pwd;

	if (!(old_pwd = getcwd(NULL, 0)))
		return (false);
	if (!set_chdir(cmd_line, dir, flag))
	{
		free(old_pwd);
		if (g_err || errno != 0)
			return (false);
		return (true);
	}
	set_env_target("OLDPWD", old_pwd);
	free(old_pwd);
	if (!set_pwd_to_env("PWD"))
		return (false);
	return (true);
}

bool		cd(t_cmd_line *cmd_line)
{
	char		*dir;
	t_list		*param_list;
	bool		flag;

	flag = false;
	param_list = cmd_line->param;
	if (!(dir = set_dir(param_list, &flag)))
		return (false);
	if (!(set_cd(cmd_line, dir, flag)))
	{
		free(dir);
		return (false);
	}
	free(dir);
	return (true);
}
