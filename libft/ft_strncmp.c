/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:01:28 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 15:19:45 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	size_t			len;
	unsigned char	*p1;
	unsigned char	*p2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	len = ft_strlen(s2) < ft_strlen(s1) ? ft_strlen(s1) : ft_strlen(s2);
	len = len <= n ? len : n;
	index = 0;
	while (p1[index] == p2[index] && index < len)
		index++;
	if (index == len)
		return (0);
	return (p1[index] - p2[index]);
}
