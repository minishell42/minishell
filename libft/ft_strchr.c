/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:33:32 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 15:17:58 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*new_s;
	size_t	s_len;

	if (!(s_len = ft_strlen(s)))
	{
		if (*s == c)
			return ((char *)s);
		else
			return (NULL);
	}
	else
		new_s = (char *)s;
	while (*new_s != '\0')
	{
		if (*new_s == c)
			return (new_s);
		new_s++;
	}
	if (c == '\0')
		return (new_s);
	return (NULL);
}
