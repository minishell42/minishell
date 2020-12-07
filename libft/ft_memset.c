/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:48:56 by dokang            #+#    #+#             */
/*   Updated: 2020/11/07 13:16:46 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int val, size_t size)
{
	unsigned char	value;
	size_t			index;

	index = 0;
	value = (unsigned char)val;
	while (index < size)
	{
		((unsigned char *)dst)[index] = value;
		index++;
	}
	return (dst);
}
