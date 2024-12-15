/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:59:02 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/18 09:20:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lst_err	*ft_lsterrlast(t_lst_err *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lsterradd_back(t_lst_err **lst, t_lst_err *new)
{
	t_lst_err	*endnode;

	if (lst)
	{
		if (*lst)
		{
			endnode = ft_lsterrlast(*lst);
			endnode->next = new;
		}
		else
			*lst = new;
	}
}

void	lstiter_err(t_data *dt, t_err *err, t_lst_err *lst
	, void (*f)(t_data *dt, t_err *, t_err_var))
{
	if (lst && f && err)
	{		
		while (lst)
		{
			(*f)(dt, err, lst->content);
			lst = lst->next;
		}
	}
}

void	lstiter_err_01(t_data *dt, t_lst_err *lst
	, void (*f)(t_data *, t_err_var))
{
	if (lst && f && dt)
	{		
		while (lst)
		{
			(*f)(dt, lst->content);
			lst = lst->next;
		}
	}
}

t_lst_err	*ft_lsterr_new(t_err_var *content)
{
	t_lst_err	*newnode;

	newnode = (t_lst_err *)malloc(sizeof (t_lst_err));
	if (newnode)
	{
		newnode->content = *content;
		if (content->arg != NULL)
			newnode->content.arg = ft_strdup(content->arg);
		newnode->next = NULL;
	}
	return (newnode);
}
