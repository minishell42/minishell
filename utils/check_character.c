#include "utils.h"

int			is_separator(int c)
{
	if (c == ';' || c == '|')
		return (true);
	return (false);
}

int			is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

int			is_semicolon(int c)
{
	if (c == ';')
	{
		return (true);
	}
	return (false);
}

bool		is_delimitor(int c)
{
	if (is_separator(c) || is_redirection(c) || is_semicolon(c))
		return (true);
	return (false);
}