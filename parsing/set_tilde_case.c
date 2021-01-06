#include "parsing.h"

char	*tilde_expansion_dir(void)
{
	char	*tilde_dir;
	char	*user_name;
	char	*home;

	home = get_env_value("HOME");
	if (!*home)
	{
		user_name = get_env_value("USER");
		tilde_dir = set_tilde_dir(user_name);
		free(user_name);
		free(home);
	}
	else
		tilde_dir = home;
	return (tilde_dir);
}

char	*set_tilde_case2(char *before_str)
{
	char	*tilde_dir;
	char	*result;

	tilde_dir = tilde_expansion_dir();
	result = ft_strjoin(tilde_dir, before_str + 1);
	free(tilde_dir);
	return (result);
}

char	*set_tilde_case3(char *before_str)
{
	char	*pwd;
	char	*tilde_dir;

	pwd = get_env_value("PWD");
	if (!*pwd)
	{
		free(pwd);
		return (ft_strdup(before_str));
	}
	tilde_dir = ft_strjoin(pwd, before_str + 2);
	free(pwd);
	return (tilde_dir);
}

char	*set_tilde_case4(char *before_str)
{
	char	*old_pwd;
	char	*tilde_dir;

	old_pwd = get_env_value("OLDPWD");
	if (!*old_pwd)
	{
		free(old_pwd);
		return (ft_strdup(before_str));
	}
	tilde_dir = ft_strjoin(old_pwd, before_str + 2);
	free(old_pwd);
	return (tilde_dir);
}

char	*set_tilde_case5(char *before_str)
{
	char	*tilde_dir;
	char	*user_name;
	char	*result;
	char	*tmp;
	DIR		*dir_ptr;

	tmp = ft_strchr(before_str, '/');
	user_name = ft_substr(before_str, 1, tmp - before_str);
	tilde_dir = set_tilde_dir(user_name);
	free(user_name);
	if (!(dir_ptr = opendir(tilde_dir)))
	{
		free(tilde_dir);
		return (ft_strdup(before_str));
	}
	closedir(dir_ptr);
	result = ft_strjoin(tilde_dir, tmp + 1);
	free(tilde_dir);
	return (result);
}
