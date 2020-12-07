/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:53:24 by dokang            #+#    #+#             */
/*   Updated: 2020/04/09 16:43:00 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		len;
	int		index;

	len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	index = 0;
	while (s[index])
	{
		new_str[index] = s[index];
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
