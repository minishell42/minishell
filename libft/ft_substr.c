/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:43:39 by dokang            #+#    #+#             */
/*   Updated: 2020/04/19 15:43:44 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_make_s(size_t len, unsigned int *max_len)
{
	char	*new_str;

	if ((long)len <= 0)
		*max_len = 0;
	else
		*max_len = (unsigned int)len;
	new_str = malloc(sizeof(char) * (*max_len + 1));
	if (!new_str)
		return (NULL);
	return (new_str);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	index;
	unsigned int	s_len;
	unsigned int	max_len;

	if (s == NULL)
		return (NULL);
	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	index = 0;
	if (start >= s_len)
		new_str = ft_make_s(0, &max_len);
	else
		new_str = ft_make_s(len, &max_len);
	if (!new_str)
		return (NULL);
	while (s[index + start] != '\0' && index < max_len)
	{
		new_str[index] = s[index + start];
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
