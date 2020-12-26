#include "utils.h"

t_list 		*get_env_llist(char *envp[])
{
	int			i;
	t_list		*env;

	i = 0;
	env = 0;
	while (envp[i])
	{
		if (env)
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(envp[i])));
		else
			env = ft_lstnew(ft_strdup(envp[i]));
		i++;
	}
	return (env);
}

char 		**convert_to_array_env_list(t_list *env)
{
	char 	**envp;
	int		len;
	int		i;

	len = ft_lstsize(env);
	envp = ft_calloc(sizeof(char *), len + 1);
	i = 0;
	while (env)
	{
		envp[i] = (char *)env->content;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
