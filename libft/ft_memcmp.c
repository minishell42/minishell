/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:11:10 by dokang            #+#    #+#             */
/*   Updated: 2020/04/09 11:06:29 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t			index;
	size_t			len;
	unsigned char	*p1;
	unsigned char	*p2;

	if (num == 0)
		return (0);
	p1 = (unsigned char *)ptr1;
	p2 = (unsigned char *)ptr2;
	len = sizeof(ptr1) < num ? sizeof(ptr1) : num;
	len = len < sizeof(ptr2) ? sizeof(ptr2) : len;
	index = 0;
	while (p1[index] == p2[index] && index < len)
		index++;
	if (index == num)
		return (0);
	return ((p1[index] - p2[index]));
}
