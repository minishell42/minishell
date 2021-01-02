#include "parsing.h"

char		*set_value_before_quote(char *str, int start, int end)
{
	char		*before_str;
	char		*result;

	before_str = ft_substr(str, start, end - start);
	result = set_multi_env(before_str);
	free(before_str);
	return (result);
}

char		*make_quote_str(char *str, int *i)
{
	char		quote;
	int			start;
	char		*quote_str;
	char		*tmp;
	char		*result;

	quote = str[*i];
	start = ++(*i);
	while (str[*i] != quote)
		(*i)++;
	quote_str = ft_substr(str, start, *i - start);
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

	while (str[*index] != '\'' && str[*index] != '\"' && str[*index])
		(*index)++;
	normal_str = set_value_before_quote(str, start, *index);
	quote_str = make_quote_str(str, index);
	result = ft_strjoin(normal_str, quote_str);
	free(normal_str);
	free(quote_str);
	return (result);
}

char		*make_valid_value(char *str)
{
	int			i;
	int			start;
	char		*result;
	char		*str_tmp;
	char		*r_tmp;

	i = 0;
	start = i;
	result = ft_calloc(sizeof(char), 1);
	while (str[i])
	{
		str_tmp = convert_to_quote_str(str, start, &i);
		r_tmp = result;
		result = ft_strjoin(r_tmp, str_tmp);
		free(r_tmp);
		if (str[i])
			i++;
		start = i;
		free(str_tmp);
	}
	return (result);
}

char		*convert_to_valid_value(char *start, int len)
{
	char		*result;
	char		*str;
	char		*tmp;

	str = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(str, start, len + 1);
	result = make_valid_value(str);
	free(str);
	return (result);
}

int			set_param(t_cmd_line *command_line, char *start)
{
	char		*param;
	int			param_len;
	int			i;

	i = 0;
	if (!check_character_in_line(start, &i, is_separator))
		return (-1);
	if (start[i] == '|')
		command_line->pipe_flag = true;
	param = ft_substr(start, 0, i);
	command_line->param = ft_lstnew(param);
	if (start[i])
		i++;
	return (i);
}
