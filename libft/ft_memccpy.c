/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:54:42 by dokang            #+#    #+#             */
/*   Updated: 2020/11/07 13:16:33 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	index;
	int		check;

	check = 1;
	index = 0;
	while (index < n && check)
	{
		((unsigned char *)dst)[index] = ((unsigned char *)src)[index];
		if (((unsigned char *)src)[index] == (unsigned char)c)
			check = 0;
		index++;
	}
	if (check)
		return (NULL);
	return (dst + index);
}
