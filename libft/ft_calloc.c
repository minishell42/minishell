/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:28:32 by dokang            #+#    #+#             */
/*   Updated: 2020/04/11 12:44:10 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*newp;
	size_t	index;

	index = 0;
	if (nmemb == 0 || size == 0)
	{
		newp = malloc(sizeof(char) * 1);
		newp[0] = 0;
		return (newp);
	}
	newp = malloc(size * nmemb);
	if (!newp)
		return (NULL);
	while (index < size * nmemb)
	{
		newp[index] = 0;
		index++;
	}
	return ((void *)newp);
}
