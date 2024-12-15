/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_std.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:45:46 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:20:08 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_err_std_01(t_err *err)
{
	set_err_var_01(err, true, FATAL, errno);
	err->v.str = strerror(errno);
	g_status = 1;
	log_hist_err(err);
	return ;
}

void	set_err_std_02(t_err *err)
{
	set_err_var_01(err, true, FATAL, 22);
	err->v.str = MSHL_EINVAL;
	g_status = 1;
	log_hist_err(err);
	return ;
}

void	set_err_var_01(t_err *err, t_bool ks, t_grv_err grav, int num)
{
	err->v.ks = ks;
	err->v.n_grv = grav;
	err->v.num = num;
	err->v.lvl = 0;
	return ;
}

void	set_err_var_02(t_err *err, t_bool ks, t_grv_err grav, int num)
{
	err->v.ks = ks;
	err->v.n_grv = grav;
	err->v.num = num;
	err->v.lvl = 0;
	return ;
}
