/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 01:24:56 by dokang            #+#    #+#             */
/*   Updated: 2020/04/21 10:52:37 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_col(char const *s, char c)
{
	int	col;

	col = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		col++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (col);
}

static char	*ft_string(char const *s, char c)
{
	char	*new_s;
	char	*temp;

	if ((temp = ft_strchr(s, c)))
		new_s = ft_substr(s, 0, temp - s);
	else
		new_s = ft_substr(s, 0, ft_strlen(s));
	return (new_s);
}

char		**ft_split(char const *s, char c)
{
	char	**new_s;
	int		col;
	int		index;

	if (s == NULL)
		return (NULL);
	col = ft_col(s, c);
	if (!(new_s = (char **)malloc(sizeof(char *) * (col + 1))))
		return (NULL);
	index = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		new_s[index] = ft_string(s, c);
		s += ft_strlen(new_s[index]);
		index++;
	}
	new_s[index] = NULL;
	return (new_s);
}
