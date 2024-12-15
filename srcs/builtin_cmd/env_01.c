/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:24:27 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 15:46:26 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static t_bool	unset_core(t_data *dt, t_err *err, char *arg)
{
	t_chk_stab_e	ret;

	ret.ks = false;
	if ((arg[0] == '-') && (arg[1] == '\0'))
		return (false);
	else if ((arg[0] == '-') && (arg[1] != '\0'))
		set_err_env_03(err);
	else if (arg[0] != '\0')
	{
		ret = chk_var_exist_env(err, &dt->env, arg);
		if (ret.ks == true)
			return (true);
		else if (ret.stab.ks == true)
		{
			free_str(&dt->env.tab[ret.stab.idx]);
			push_up_env_tab(err, &dt->env, ret.stab.idx);
		}
	}
	return (false);
}

int	ft_unset_env(t_data *dt, char **var_name)
{
	t_err			err;
	register size_t	i;

	i = 0;
	init_error_data(&err);
	if (var_name)
	{
		while (var_name[i] != NULL)
		{
			if (unset_core(dt, &err, var_name[i]) == true)
				break ;
			i++;
		}
	}
	if (err.v.ks == true)
		print_builtin_error(&err, MSHL_DLG_ERR_UNSET);
	return (err.v.num);
}

int	ft_env(t_data *dt, char **var_name)
{
	t_err	err;

	init_error_data(&err);
	if (*var_name)
	{
		set_err_var_01(&err, true, NORMAL, 22);
		err.v.str = MSHL_EINVAL;
	}
	else
		print_env_sort(dt, &err, true);
	if (err.v.ks == true)
		print_builtin_error(&err, MSHL_DLG_ERR_ENV);
	return (err.v.num);
}
