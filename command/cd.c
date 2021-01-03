#include "command.h"

static bool	set_chdir(char *dir, bool flag)
{
	if (chdir(dir) < 0)
	{
		make_err_msg(EXIT_FAILURE, "cd", dir,
					get_err_msg(NO_FILE_OR_DIRECTORY));
		free(dir);
		return (false);
	}
	if (flag)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	return (true);
}

static bool	set_pwd_to_env(char *env_value, char *dir)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	set_env_target(env_value, pwd);
	free(pwd);
	return (true);
}

bool		cd(t_cmd_line *cmd_line)
{
	char		*dir;
	char		*old_pwd;
	t_list		*param_list;
	bool		flag;

	flag = false;
	param_list = cmd_line->param;
	if (!(dir = set_dir(param_list, &flag)))
		return (false);
	if (!(old_pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	if (!set_chdir(dir, flag))
	{
		free(old_pwd);
		return (false);
	}
	set_env_target("OLDPWD", old_pwd);
	free(old_pwd);
	if (!set_pwd_to_env("PWD", dir))
		return (false);
	free(dir);
	return (true);
}
