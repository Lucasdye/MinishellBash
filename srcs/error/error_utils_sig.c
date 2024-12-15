/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_sig.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:28:27 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 07:43:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	chk_error_sig(t_data *dt)
{
	if (dt->ks_exit == true)
		write(1, MSHL_DLG_EXIT, 5);
	if (dt->err.v.num != 0)
		dt->last_err = dt->err.v.num;
	if ((dt->err.v.num != 0) && (dt->err.v.num != 130))
		print_error(dt);
	if (g_status != 0)
		dt->last_err = g_status;
	return ;
}

void	chk_error_sig_buitin(t_err *err, char *src)
{
	if (err->v.ks == true)
		print_builtin_error(err, src);
	if (g_status != 0)
		err->v.num = g_status;
	return ;
}
