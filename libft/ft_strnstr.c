/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:45:20 by dokang            #+#    #+#             */
/*   Updated: 2020/04/11 12:38:28 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b_index;
	size_t	l_len;
	char	*result;

	if (*little == '\0')
		return ((char *)big);
	l_len = ft_strlen(little);
	b_index = 0;
	while (*big != '\0' && b_index < len)
	{
		result = (char *)big;
		if (b_index + l_len <= len)
		{
			if (!ft_strncmp(big, little, l_len))
				return (result);
		}
		big++;
		b_index++;
	}
	return (NULL);
}
