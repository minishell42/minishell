#include "utils.h"

t_list 		*get_env_llist(char *envp[])
{
	int			i;
	char		*env_str;
	t_list		*env;
	t_list		*new_list;

	i = 0;
	env = 0;
	while (envp[i])
	{
		if (!(env_str = ft_strdup(envp[i])) || !(new_list = ft_lstnew(env_str)))
		{
			built_in_error();
			exit(EXIT_FAILURE);
		}
		if (env)
			ft_lstadd_back(&env, new_list);
		else
			env = new_list;
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
