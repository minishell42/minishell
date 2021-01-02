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
