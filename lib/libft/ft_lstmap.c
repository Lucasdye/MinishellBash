/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:26:00 by jveuille          #+#    #+#             */
/*   Updated: 2022/11/20 18:26:19 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rootnode;
	t_list	*newlist;

	if (!(lst && f && del))
		return (NULL);
	rootnode = NULL;
	while (lst)
	{
		newlist = ft_lstnew((*f)(lst->content));
		if (newlist != NULL)
		{
			ft_lstadd_back(&rootnode, newlist);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&rootnode, del);
			return (NULL);
		}
	}
	return (rootnode);
}
