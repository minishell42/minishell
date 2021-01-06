#include "command.h"

static bool	old_pwd_dir(char **dir, bool *flag)
{
	*dir = get_env_value("OLDPWD");
	if (**dir == '\0')
	{
		make_err_msg(EXIT_FAILURE, "cd", 0, get_err_msg(NO_OLDPWD));
		free(*dir);
		return (false);
	}
	*flag = true;
	return (true);
}

static char	*set_dir_param(t_list *param_list)
{
	char	*param;
	int		list_size;

	list_size = ft_lstsize(param_list);
	if (list_size > 1)
	{
		make_err_msg(EXIT_FAILURE, "cd", 0, get_err_msg(TOO_MANY_REDIR_PARAM));
		return (NULL);
	}
	else if (!list_size)
		param = ft_strdup("--");
	else
		param = ft_strdup(param_list->content);
	return (param);
}

static char	*set_home_dir(void)
{
	char	*home;
	char	*dir;

	home = get_env_value("HOME");
	if (*home == '\0')
	{
		make_err_msg(EXIT_FAILURE, "cd", 0, get_err_msg(NO_HOME));
		return (NULL);
	}
	dir = ft_strdup(home);
	free(home);
	return (dir);
}

char		*set_dir(t_list *param_list, bool *flag)
{
	char	*dir;
	char	*param;

	if (!(param = set_dir_param(param_list)))
		return (NULL);
	if (param[0] == '-' && ft_strlen(param) == 1)
	{
		if (!old_pwd_dir(&dir, flag))
		{
			free(param);
			return (NULL);
		}
	}
	else if (are_equal(param, "--"))
		dir = set_home_dir();
	else
		dir = ft_strdup(param);
	free(param);
	return (dir);
}
