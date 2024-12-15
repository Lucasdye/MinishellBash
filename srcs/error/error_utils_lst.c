/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:12:01 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/18 09:18:49 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	log_hist_err(t_err *err)
{
	t_lst_err	*newnode;

	if (err->hist_err == NULL)
		err->hist_err = ft_lsterr_new(&err->v);
	else
	{
		newnode = ft_lsterr_new(&err->v);
		ft_lsterradd_back(&err->hist_err, newnode);
	}
	return ;
}

void	log_hist_err_01(t_data *dt)
{
	t_lst_err	*newnode;

	if (dt->err.hist_err == NULL)
		dt->err.hist_err = ft_lsterr_new(&dt->err.v);
	else
	{
		newnode = ft_lsterr_new(&dt->err.v);
		ft_lsterradd_back(&dt->err.hist_err, newnode);
	}
	return ;
}

void	clear_hist_err(t_err *err)
{
	t_lst_err	*node;

	if (err->hist_err && *(&err->hist_err))
	{
		while (*(&err->hist_err))
		{
			node = (*(&err->hist_err))->next;
			if (err->hist_err->content.arg != NULL)
				free(err->hist_err->content.arg);
			free(err->hist_err);
			*(&err->hist_err) = node;
		}
		err->hist_err = NULL;
	}
	return ;
}
