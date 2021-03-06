/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_param_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangpark <sangpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:44:25 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/03 05:44:54 by sangpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char		*make_param(char *param, int start, int len)
{
	char	*tmp;
	char	*arg;
	char	*result;

	tmp = ft_substr(param, start, len);
	if (!tmp)
		return (NULL);
	arg = convert_to_valid_value(tmp, ft_strlen(tmp));
	free(tmp);
	if (!arg)
		return (NULL);
	result = apply_tilde_expansion(arg);
	free(arg);
	return (result);
}

t_list			*make_param_list(char *param)
{
	t_list	*args_list;
	int		start;
	int		index;
	char	*arg;

	index = 0;
	while (param[index] && ft_isspace(param[index]))
		index++;
	start = index;
	args_list = NULL;
	while (param[index] && check_character_in_line(param, &index, ft_isspace))
	{
		arg = make_param(param, start, index - start);
		if (!arg)
			return (args_list);
		if (!args_list)
			args_list = ft_lstnew(arg);
		else
			ft_lstadd_back(&args_list, ft_lstnew(arg));
		while (param[index] && ft_isspace(param[index]))
			index++;
		start = index;
	}
	return (args_list);
}
