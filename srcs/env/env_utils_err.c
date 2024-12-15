/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:43:02 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 09:20:15 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_err_env_01(t_err *err)
{
	set_err_var_01(err, true, NORMAL, 2);
	err->v.str = MSHL_NOT_YET_FUNC;
	return ;
}

void	set_err_env_02(t_err *err)
{
	set_err_var_01(err, true, NORMAL, 1);
	err->v.str = MSHL_NOVALID_VAR_EXPORT;
	return ;
}

void	set_err_env_03(t_err *err)
{
	set_err_var_01(err, true, NORMAL, 2);
	err->v.str = MSHL_NOVALID_ARG_EXPORT_02;
	return ;
}

void	set_err_env_04(t_err *err)
{
	set_err_var_01(err, true, NORMAL, 2);
	err->v.str = MSHL_NULL_PARA;
	return ;
}
