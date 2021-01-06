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

char	*apply_tilde_expansion(char *before_str)
{
	int			apply_case;

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
	return (ft_strdup(before_str));
}
