/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 00:42:53 by dokang            #+#    #+#             */
/*   Updated: 2020/04/21 10:53:07 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s1, char const *set)
{
	char	*temp;
	int		s_len;

	s_len = ft_strlen(s1) - 1;
	if (s_len < 0)
		return (0);
	temp = (char *)s1 + s_len;
	while (s_len >= 0)
	{
		if (!ft_strchr(set, *temp))
			break ;
		else
		{
			temp--;
			s_len--;
		}
	}
	return (s_len + 1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*new_s;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	if (*s1 == '\0')
		len = 0;
	else
		len = ft_len(s1, set);
	new_s = ft_substr(s1, 0, len);
	return (new_s);
}
