/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_var_ini.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:36:19 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 13:41:36 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_chk_var(t_chk_stab_e *chk)
{
	chk->ks = true;
	chk->stab.ks = false;
	chk->stab.idx = 0;
	return ;
}

t_bool	set_err_init(t_err *err, char *str)
{
	t_bool	ks;

	ks = false;
	if (!str)
	{
		set_err_env_04(err);
		ks = true;
	}
	else if (str[0] == EQUAL)
	{
		set_err_env_02(err);
		ks = true;
	}
	return (ks);
}
