/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:04:42 by jveuille          #+#    #+#             */
/*   Updated: 2023/04/12 10:02:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*endnode;

	if (lst)
	{
		if (*lst)
		{
			endnode = ft_lstlast(*lst);
			endnode->next = new;
		}
		else
			*lst = new;
	}
}
