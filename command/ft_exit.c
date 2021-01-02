/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 01:18:08 by dokang            #+#    #+#             */
/*   Updated: 2021/01/03 01:18:11 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	*ft_exit(t_cmd_line *cmd_line)
{
	free_cmd_struct(cmd_line);
	free_env_list(&g_env);
	process_exit(0);
}
