/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:00:37 by dokang            #+#    #+#             */
/*   Updated: 2021/01/07 17:00:39 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	free_export(t_export *exp_info)
{
	if (exp_info->env_key)
		free(exp_info->env_key);
	free(exp_info);
}

void	print_content_exp(void *content)
{
	int		len;
	char	*str;

	if (!content)
		return ;
	str = content;
	len = ft_strlen(content);
	str[len] = '\n';
	write(1, "declare -x ", 11);
	write(1, str, len + 1);
	str[len] = '\0';
}
