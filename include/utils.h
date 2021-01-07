/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:15:12 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:15:13 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "ft_error.h"

/*
** string_util.c
*/
void		remove_quotation(char *value);
void		free_str_array(char **strs);
bool		is_contained(char c, char *str);
char		*ft_join_strs(char **strs);
int			is_seperate_character(int c);

/*
** check_character.c
*/
int			is_separator(int c);
int			is_redirection(int c);
int			is_semicolon(int c);
bool		is_delimitor(int c);
bool		is_empty_line(char *line);

/*
** env_llist.c
*/
t_list		*get_env_llist(char *envp[]);
char		**convert_to_array_env_list(t_list *env);

#endif
