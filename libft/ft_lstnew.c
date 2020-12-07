/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:04:28 by dokang            #+#    #+#             */
/*   Updated: 2020/04/07 20:48:10 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_t;

	if (!(new_t = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_t->content = content;
	new_t->next = NULL;
	return (new_t);
}
