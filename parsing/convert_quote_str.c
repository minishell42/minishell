/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quote_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: park <park@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 04:43:07 by sangpark          #+#    #+#             */
/*   Updated: 2021/01/05 11:40:25 by park             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char		*set_value_before_quote(char *str, int start, int *index)
{
	char		*before_str;
	int			bef_idx;
	char		*result;

	bef_idx = 0;
	before_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[*index] && str[*index] != '\'' && str[*index] != '\"')
	{
		if (str[*index] == '\\')
			before_str[bef_idx++] = str[++(*index)];
		else
			before_str[bef_idx++] = str[*index];
		(*index)++;
	}
	result = set_multi_env(before_str);
	free(before_str);
	return (result);
}

char		*make_quote_str(char *str, int *i)
{
	char		quote;
	int			len;
	char		*quote_str;
	char		*tmp;

	if (!(quote = str[*i]))
		return (NULL);
	quote_str = ft_calloc(sizeof(char), ft_strlen(str));
	len = 0;
	while (str[++(*i)] != quote)
	{
		if (quote == '"' && str[*i] == '\\' && str[*i + 1] == '\"')
			quote_str[len++] = str[++(*i)];
		else
			quote_str[len++] = str[*i];
	}
	if (quote == '\'')
		return (quote_str);
	else if (quote == '\"')
	{
		tmp = quote_str;
		quote_str = set_multi_env(quote_str);
		free(tmp);
	}
	return (quote_str);
}

char		*convert_to_quote_str(char *str, int start, int *index)
{
	char		*normal_str;
	char		*quote_str;
	char		*result;

	normal_str = set_value_before_quote(str, start, index);
	quote_str = make_quote_str(str, index);
	result = ft_strjoin(normal_str, quote_str);
	free(normal_str);
	free(quote_str);
	return (result);
}
