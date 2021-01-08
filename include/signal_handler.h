/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:14:50 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:14:52 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include "pipe.h"
# include <signal.h>

# define I_CYAN		"\033[3;36m"
# define B_YELLOW	"\033[1;33m"
# define WHITE		"\033[0;39m"

/*
** set_prompt.c
*/
void		prompt(void);
void		process_exit(bool option);
/*
** signal_handler.c
*/
void		init_child_signal(void);
void		init_signal(void);
void		signal_ignore(void);
void		default_signal(int signal_no);

#endif
