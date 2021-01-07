/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:20:32 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:20:34 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void		prompt(void)
{
	char	*str;

	str = I_CYAN"minishell "B_YELLOW"$ "WHITE;
	write(1, str, ft_strlen(str));
}

void		process_exit(bool option)
{
	char	*str;

	if (option)
		ft_putstr_fd("exit\n", 1);
	str = B_YELLOW"minishell exit\n";
	write(1, str, ft_strlen(str));
	exit(0);
}
