/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:09:03 by dokang            #+#    #+#             */
/*   Updated: 2020/11/07 13:17:03 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	result;
	size_t	index;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len > size)
		result = src_len + size;
	else
		result = dst_len + src_len;
	if (size == 0)
		return (result);
	index = 0;
	while (src[index] && index + dst_len < size - 1)
	{
		dst[dst_len + index] = src[index];
		index++;
	}
	dst[dst_len + index] = '\0';
	return (result);
}
