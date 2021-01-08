/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:20:40 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:20:41 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void		default_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		ft_putstr_fd(" \b\b \b\b \b\n", 1);
		prompt();
	}
	else if (signal_no == SIGQUIT)
		ft_putstr_fd(" \b\b \b\b \b", 1);
}

void		child_signal(int signal_no)
{
	if (signal_no == SIGINT)
		exit(INVALID_ARGUMENT_TO_EXIT + signal_no);
	else if (signal_no == SIGQUIT)
		exit(INVALID_ARGUMENT_TO_EXIT + signal_no);
}

void		override_signal(int signal_no)
{
	if (signal_no == SIGINT)
		ft_putchar_fd('\n', 1);
	else if (signal_no == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void		signal_ignore(void)
{
	signal(SIGINT, override_signal);
	signal(SIGQUIT, override_signal);
}

void		init_child_signal(void)
{
	signal(SIGINT, child_signal);
	signal(SIGQUIT, child_signal);
}
