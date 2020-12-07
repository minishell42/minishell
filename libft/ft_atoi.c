/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:37:12 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 12:27:13 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	char *str;

	str = "\n\t \r\v\f";
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static int	ft_check_max_min(const char *nptr, int minus)
{
	char	*long_max;
	char	*long_min;
	int		eof_val;
	char	*check_val;

	long_max = (char[]){"9223372036854775807"};
	long_min = (char[]){"9223372036854775808"};
	eof_val = 0;
	if (minus < 0)
		check_val = long_min;
	else
		check_val = long_max;
	while (ft_isdigit(*nptr))
	{
		if (*nptr < *check_val)
			return (1);
		else
			eof_val++;
		nptr++;
		long_max++;
		if (eof_val >= 19)
			return (0);
	}
	return (1);
}

static long	ft_make_nbr(const char *nptr, int minus)
{
	long	num;

	num = 0;
	if (!ft_check_max_min(nptr, minus))
	{
		if (minus < 0)
			return (0);
		else
			return (-1);
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	num *= minus;
	return (num);
}

int			ft_atoi(const char *nptr)
{
	long	minus;
	long	num;

	minus = 1;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus *= -1;
		nptr++;
	}
	num = ft_make_nbr(nptr, minus);
	return ((int)num);
}
