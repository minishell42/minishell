#include "minishell.h"

t_list 		*get_env_llist(char *envp[])
{
	int			i;
	t_list		*env;

	i = 0;
	env = 0;
	while (envp[i])
	{
		if (env)
			ft_lstadd_back(&env, ft_lstnew(envp[i]));
		else
			env = ft_lstnew(envp[i]);		
		i++;
	}
	return (env);
}
