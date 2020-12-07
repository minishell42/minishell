/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:33:45 by dokang            #+#    #+#             */
/*   Updated: 2020/04/11 12:58:02 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	s_len;
	int		index;

	if (s == NULL || f == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (!(new_s = (char *)malloc(sizeof(char) * (s_len + 1))))
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		new_s[index] = f(index, s[index]);
		index++;
	}
	new_s[index] = '\0';
	return (new_s);
}
