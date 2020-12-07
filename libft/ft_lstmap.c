/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokang <dokang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:01:20 by dokang            #+#    #+#             */
/*   Updated: 2020/11/07 13:16:19 by dokang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*sn;
	t_list	*temp;
	int		checker;

	checker = 1;
	if (lst == NULL)
		return (NULL);
	if (!(n_list = (t_list *)malloc(sizeof(t_list))))
	{
		ft_lstdelone(n_list, del);
		return (NULL);
	}
	temp = lst;
	while (temp != NULL)
	{
		sn = ft_lstnew(f(temp->content));
		if (checker)
			n_list = NULL;
		ft_lstadd_back(&n_list, sn);
		checker = 0;
		temp = temp->next;
	}
	return (n_list);
}
