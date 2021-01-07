/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_are_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:17:38 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:17:39 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	are_equal(char *s1, char *s2)
{
	int			s1_len;
	int			s2_len;

	if (!s1 && !s2)
		return (true);
	if (!s1 || !s2)
		return (false);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len == s2_len && ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (true);
	return (false);
}
