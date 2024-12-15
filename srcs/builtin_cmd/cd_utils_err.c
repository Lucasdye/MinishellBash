/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:28:56 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 15:46:47 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_err_cd_01(t_err *err)
{
	set_err_var_01(err, true, CRITICAL, 1);
	err->v.str = MSHL_NOVALID_HOME_CD;
	return ;
}

void	set_err_cd_02(t_err *err)
{
	set_err_var_01(err, true, FATAL, 1);
	err->v.str = MSHL_DEFECTIVE_DRIVE;
	set_str_arg_builtin(err, &err->v.arg, "'/'");
	return ;
}

void	set_err_cd_03(t_err *err)
{
	set_err_var_01(err, true, NORMAL, 1);
	err->v.str = MSHL_OVER_ARG;
	return ;
}
