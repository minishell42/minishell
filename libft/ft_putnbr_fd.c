/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:07:30 by dokang            #+#    #+#             */
/*   Updated: 2020/04/13 10:41:37 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int s;

	s = 0;
	if (n >= 0)
		s = n;
	if (n < 0)
	{
		s = n * -1;
		ft_putchar_fd('-', fd);
	}
	if (s > 9)
		ft_putnbr_fd(s / 10, fd);
	ft_putchar_fd((s % 10) + '0', fd);
}
