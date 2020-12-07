/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:49:25 by dokang            #+#    #+#             */
/*   Updated: 2020/11/07 13:13:56 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = (*lst);
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast(temp);
		temp->next = new;
	}
}
