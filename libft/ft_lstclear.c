/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:00:35 by dokang            #+#    #+#             */
/*   Updated: 2020/11/07 13:14:08 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*temp;
	t_list	*tnext;

	if (del == NULL)
		return ;
	if (*list != NULL)
	{
		temp = *list;
		while (temp->next != NULL)
		{
			tnext = temp->next;
			ft_lstdelone(temp, del);
			temp = tnext;
		}
		del(temp->content);
		free(temp);
	}
	*list = NULL;
}
