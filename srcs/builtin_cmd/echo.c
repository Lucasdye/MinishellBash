/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:28 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/18 18:32:44 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_echo_prnt(t_err *err, register size_t i, char **arg)
{
	t_bool	ks;

	ks = false;
	while ((arg[i] != NULL) && (ks == false))
	{
		ks = ft_swrite(err, arg[i], STDOUT_FILENO);
		if (ks == false)
		{
			if (arg[i + 1] != NULL)
				ks = ft_swrite(err, "\x20", STDOUT_FILENO);
		}
		i++;
	}
	return (ks);
}

static t_bool	ft_chk_echo_opt(t_err *err, t_bool *ks_lf, char **arg)
{
	register size_t	i;
	t_bool			ks;
	t_chk_str		chk;
	t_bool			ks_w;

	ks = false;
	i = 0;
	while ((arg[i] != NULL) && (ks == false))
	{
		if ((ft_strlen(arg[i]) != 2) || (arg[i][0] != MINUS))
			ks = true;
		else
		{
			chk = ft_srchstr(arg[i][1], MSHL_ECHO_OPT);
			if (chk.ks == false)
				ks = true;
			else if (MSHL_ECHO_OPT[chk.idx] == 'n')
				*ks_lf = false;
		}
		if (ks == false)
			i++;
	}
	ks_w = ft_echo_prnt(err, i, arg);
	return (ks_w);
}

int	ft_echo(t_data *dt, char **var_name)
{
	t_err	err;
	t_bool	ks_lf;
	t_bool	ks_w;

	(void)dt;
	ks_lf = true;
	ks_w = false;
	init_error_data(&err);
	if ((var_name == NULL) || (var_name[0] == NULL))
		ks_lf = true;
	else
		ks_w = ft_chk_echo_opt(&err, &ks_lf, var_name);
	if ((ks_lf == true) && (ks_w == false))
		ft_swrite(&err, "\n", STDOUT_FILENO);
	if (err.v.ks == true)
		print_builtin_error(&err, MSHL_DLG_ERR_ECHO);
	return (err.v.num);
}
