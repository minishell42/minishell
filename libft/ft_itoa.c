/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:52:24 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 15:13:18 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_set_number(char *str, long num, int len)
{
	char	c;

	str[len] = '\0';
	len--;
	while (num / 10 != 0)
	{
		c = num % 10 + '0';
		str[len] = c;
		num /= 10;
		len--;
	}
	c = num % 10 + '0';
	str[len] = c;
}

static int	ft_num_len(int n)
{
	int		len;
	long	num;

	len = 0;
	num = (long)n;
	if (num < 0)
		len++;
	while ((num /= 10) != 0)
		len++;
	len++;
	return (len);
}

char		*ft_itoa(int n)
{
	char	*new_s;
	long	num;
	int		len;

	len = ft_num_len(n);
	if (!(new_s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		*new_s = '-';
	}
	ft_set_number(new_s, num, len);
	return (new_s);
}
