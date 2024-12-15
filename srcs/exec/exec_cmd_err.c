/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:08:19 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 07:48:58 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	set_err_cmd_01(t_data *dt, char *cmd)
{
	char	*s1;

	s1 = NULL;
	free_str(&dt->err.v.arg);
	set_err_var_01(&dt->err, true, CRITICAL, MSHL_NOFOUND_NUM);
	dt->err.v.str = NULL;
	set_str_arg(&dt->err, &dt->err.v.arg, MSHL_CMD);
	set_str_arg(&dt->err, &s1, cmd);
	ft_strjcat(&dt->err.v.arg, s1);
	free_str(&s1);
	set_str_arg(&dt->err, &s1, MSHL_NOFOUND);
	ft_strjcat(&dt->err.v.arg, s1);
	free(s1);
	log_hist_err_01(dt);
	return (true);
}

void	set_err_cmd_02(t_data *dt)
{
	set_err_var_01(&dt->err, true, CRITICAL, errno);
	dt->err.v.str = strerror(errno);
	log_hist_err_01(dt);
	return ;
}

t_bool	set_err_cmd_03(t_data *dt, char *cmd)
{
	char	*s1;

	s1 = NULL;
	free_str(&dt->err.v.arg);
	set_err_var_01(&dt->err, true, CRITICAL, MSHL_ISDIR_NUM);
	dt->err.v.str = NULL;
	set_str_arg(&dt->err, &dt->err.v.arg, MSHL_CMD);
	set_str_arg(&dt->err, &s1, cmd);
	ft_strjcat(&dt->err.v.arg, s1);
	free_str(&s1);
	set_str_arg(&dt->err, &s1, MSHL_ISDIR);
	ft_strjcat(&dt->err.v.arg, s1);
	free(s1);
	log_hist_err_01(dt);
	return (true);
}
