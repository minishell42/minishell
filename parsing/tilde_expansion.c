#include "parsing.h"
// ~
// The value of $HOME
// $HOME doesn't exist /home + username;

// ~/foo
// $HOME/foo

// ~fred/foo
// The subdirectory foo of the home directory of the user fred

// ~+/foo
// $PWD/foo

// ~-/foo
// ${OLDPWD-'~-'}/foo

// ~N
// The string that would be displayed by ‘dirs +N’

// ~+N
// The string that would be displayed by ‘dirs +N’

// ~-N
// The string that would be displayed by ‘dirs -N’

// ~가 뜻하는 경로를 가져오기
char	*tilde_expansion_dir(void)
{
	char	*tilde_dir;
	char	*user_name;
	char	*home;

	home = get_env_value("HOME");
	if (!*home)
	{
		user_name = get_env_value("USER");
		tilde_dir = ft_strjoin("/home/", user_name);
		free(user_name);
	}
	else
		tilde_dir = home;
	return (tilde_dir);
}

int		can_apply_tilde_expansion(char *before_str)
{
	if (*before_str == '~')
	{
		if (!before_str[1])
			return (1);
		else if (before_str[1] == '/')
			return (2);
		else if (before_str[1] == '+')
		{
			if (before_str[2] != '/')
				return (-1);
			return (3);
		}
		else if (before_str[1] == '-')
		{
			if (before_str[2] != '/')
				return (-1);
			return (4);
		}
		else if (ft_strchr(before_str, '/'))
			return (5);		
	}
	return (-1);
}

char	*set_tilde_case2(char *before_str)
{
	char	*tilde_dir;
	char	*result;
	char	*other_dir;

	tilde_dir = tilde_expansion_dir();
	result = ft_strjoin(tilde_dir, before_str + 1);
	free(tilde_dir);
	return (result);
}

static char	*set_tilde_case3(char *before_str)
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

static char	*set_tilde_case4(char *before_str)
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

static char	*set_tilde_case5(char *before_str)
{
	char	*tilde_dir;
	char	*user_name;
	char	*result;
	char	*tmp;
	DIR		*dir_ptr;

	tmp = ft_strchr(before_str, '/');
	user_name =ft_substr(before_str, 1, tmp - before_str);
	tilde_dir = ft_strjoin("/home/", user_name);
	free(user_name);
	if (!(dir_ptr = opendir(tilde_dir)))
	{
		free(tilde_dir);
		closedir(dir_ptr);
		return (ft_strdup(before_str));
	}
	closedir(dir_ptr);
	result = ft_strjoin(tilde_dir, tmp + 1);
	free(tilde_dir);
	return (result);
}

char	*apply_tilde_expansion(char *before_str)
{
	int	apply_case;

	if ((apply_case = can_apply_tilde_expansion(before_str)) < 0)
		return (ft_strdup(before_str));
	if (apply_case == 1)
		return (tilde_expansion_dir());
	else if (apply_case == 2)
		return (set_tilde_case2(before_str));
	else if (apply_case == 3)
		return (set_tilde_case3(before_str));
	else if (apply_case == 4)
		return (set_tilde_case4(before_str));
	else if (apply_case == 5)
		return (set_tilde_case5(before_str));
	
}