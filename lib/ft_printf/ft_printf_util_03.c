/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:22:13 by jveuille          #+#    #+#             */
/*   Updated: 2023/06/21 11:30:15 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_exit_err(t_print *dt)
{
	dt->exit.ks_err = TRUE;
	dt->exit.str = NULL;
	return ;
}

void	mem_free(t_print *dt)
{
	free(dt->str_tmp);
	free(dt->str_buff);
	return ;
}

char	set_exit_str(t_print *dt)
{
	if (dt->str_buff)
	dt->exit.str = ft_calloc((dt->idx_buff + 1), sizeof(char));
	if (dt->exit.str == NULL)
		return (TRUE);
	ft_strlcpy(dt->exit.str, dt->str_buff, dt->idx_buff);
	return (FALSE);
}
