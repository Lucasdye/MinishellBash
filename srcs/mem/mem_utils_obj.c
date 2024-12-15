/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:04:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/08 09:23:06 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tstr(t_str *dest)
{
	if (dest->str != NULL)
	{
		free(dest->str);
		dest->str = NULL;
	}
	dest->idx = 0;
	dest->size = 0;
	return ;
}

void	free_obj(t_dup *dest)
{
	if (dest->str != NULL)
	{
		free(dest->str);
		dest->str = NULL;
	}
	dest->ptr = 0;
	dest->size = 0;
	return ;
}

void	free_all_obj(t_exp_var *sd)
{
	free_obj(&sd->s);
	free_obj(&sd->s_var);
	free_obj(&sd->s_line);
	return ;
}

void	free_bk(t_data *dt)
{
	free(dt->bk.pipe);
	free(dt->bk.pid);
	return ;
}
