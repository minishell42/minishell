/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:01:48 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:01:50 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

bool	pwd(void)
{
	char	*dir;
	char	*tmp;

	if (!(tmp = getcwd(NULL, 0)))
		return (false);
	dir = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!(write(1, dir, ft_strlen(dir))))
		return (false);
	free(dir);
	return (true);
}
