/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:13:07 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/26 15:16:00 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_error_tab(t_err *err)
{
	err->grav[0].num = INFO;
	err->grav[0].str = MSHL_DLG_GRV_INF;
	err->grav[1].num = WARNING;
	err->grav[1].str = MSHL_DLG_GRV_WRN;
	err->grav[2].num = NORMAL;
	err->grav[2].str = MSHL_DLG_GRV_NRM;
	err->grav[3].num = CRITICAL;
	err->grav[3].str = MSHL_DLG_GRV_CRTL;
	err->grav[4].num = FATAL;
	err->grav[4].str = MSHL_DLG_GRV_FTL;
	return ;
}

char	*set_err_tab(t_err *err, t_grv_err gravity)
{
	register int	i;

	i = 0;
	while (i < MSHL_DLG_GRV_SIZE)
	{
		if (err->grav[i].num == gravity)
			return (err->grav[i].str);
		i++;
	}
	return (NULL);
}
