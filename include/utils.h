#ifndef UTILS_H
# define UTILS_H

# include "ft_error.h"

/*
** string_util.c
*/
void		remove_quotation(char *value);
/*
** check_character.c
*/
int			is_separator(int c);
int			is_redirection(int c);
int			is_semicolon(int c);
bool		is_delimitor(int c);
bool		is_empty_line(char *line);

#endif