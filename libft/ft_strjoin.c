/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:11:41 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 15:27:14 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_copy(char *new_s, char const *s1, char const *s2)
{
	int	index;

	index = 0;
	while (*s1 != '\0')
	{
		new_s[index] = *s1;
		s1++;
		index++;
	}
	while (*s2 != '\0')
	{
		new_s[index] = *s2;
		s2++;
		index++;
	}
	new_s[index] = '\0';
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_s)
		return (NULL);
	ft_copy(new_s, s1, s2);
	return (new_s);
}
