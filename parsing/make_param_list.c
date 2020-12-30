#include "parsing.h"

static char		*make_param(char *param, int start, int len)
{
	char	*tmp;
	char	*arg;

	tmp = ft_substr(param, start, len);
	if (!tmp)
		return (NULL);
	arg = convert_to_valid_value(tmp, ft_strlen(tmp));
	free(tmp);
	if (!arg)
		return (NULL);
	return (arg);
}

t_list	*make_param_list(char *param)
{
	t_list	*args_list;
	int		start;
	int		index;
	char	*arg;

	index = 0;
	while (ft_isspace(param[index]))
		index++;
	start = index;
	args_list = NULL;
	// printf("param ? '%s'\n", param);
	while (param[index] && check_character_in_line(param, &index, ft_isspace))
	{
		arg = make_param(param, start, index - start);
		// printf("arg ? '%s'\n", arg);
		if (!arg)
			return (NULL);
		ft_lstadd_back(&args_list, ft_lstnew(arg));
		while (param[index] && ft_isspace(param[index]))
			index++;
		start = index;
		// printf("index ? %d\tstart ? %d\n", index, start);
	}
	return (args_list);
}

// char	*make_redir_param(char *param, t_list *env)
// {
// 	int		index;
// 	int		start;

// 	index = 1;
// 	while (ft_isspace(param[index]))
// 		index++;
// 	start = index;
// 	while (param[index] && ft_isspace)
// }