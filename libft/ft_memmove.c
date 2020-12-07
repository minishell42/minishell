/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:04:02 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 15:16:31 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*temp;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst <= src)
	{
		temp = dst;
		while (n--)
		{
			*((char *)temp) = *((char *)src);
			temp++;
			src++;
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
