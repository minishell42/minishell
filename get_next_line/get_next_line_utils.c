/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangpark <sangpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:26:30 by sangpark          #+#    #+#             */
/*   Updated: 2020/05/09 19:26:32 by sangpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t				count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned			i;

	if (!dst)
		return (0);
	i = 0;
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char				*res;
	int					s1_len;
	int					s2_len;
	int					i;
	int					max;

	s1_len = s1 ? ft_strlen(s1) : 0;
	s2_len = s2 ? ft_strlen(s2) : 0;
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!res)
		return (0);
	i = 0;
	max = s1_len > s2_len ? s1_len : s2_len;
	while (i < max)
	{
		if (i < s1_len)
			res[i] = s1[i];
		if (i < s2_len)
			res[i + s1_len] = s2[i];
		i++;
	}
	res[s1_len + s2_len] = '\0';
	return (res);
}

char		*ft_strchr(const char *s, int c)
{
	int					i;
	unsigned char		target;

	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	target = c;
	while (s[i])
	{
		if (s[i] == target)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
