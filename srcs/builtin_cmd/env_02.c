/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:13:06 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 15:51:16 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

inline static t_bool	chk_error(t_err *err, char *arg)
{
	if ((arg[0] == '\0') || ((arg != NULL) && (ft_isdigit(arg[0]) == true))
		|| ((arg[0] == '-') && (arg[1] == '\0'))
		|| (arg[0] == EQUAL))
	{
		set_err_env_02(err);
		return (true);
	}
	else if ((arg[0] == '-') && (arg[1] != '\0'))
	{
		set_err_env_03(err);
		return (true);
	}
	return (false);
}

inline static t_bool	export_core(t_data *dt, t_err *err
	, t_chk_stab_e ret, char *arg)
{
	ret = chk_var_exist_env(err, &dt->env, arg);
	if (ret.ks == true)
		return (true);
	else if (ret.stab.ks == true)
	{
		free(dt->env.tab[ret.stab.idx]);
		if (set_str_arg(err, &dt->env.tab[ret.stab.idx], arg) == true)
			return (true);
	}
	else
	{
		if (dt->env.idx == dt->env.size)
		{
			if (resize_env_tab(err, &dt->env, (dt->env.size + 1)) == true)
				return (true);
		}
		if (set_str_arg_builtin(err, &dt->env.tab[dt->env.idx], arg) == true)
			return (true);
		dt->env.idx++;
		dt->env.tab[dt->env.idx] = NULL;
	}
	return (false);
}

int	ft_export_env(t_data *dt, char **var_name)
{
	t_err			err;
	register size_t	i;
	t_chk_stab_e	ret;

	i = 0;
	ret.ks = false;
	init_error_data(&err);
	if (var_name[0] == NULL)
		print_env_sort(dt, &err, false);
	else
	{
		while (var_name[i] != NULL)
		{
			if (chk_error(&err, var_name[i]) == false)
			{
				if (export_core(dt, &err, ret, var_name[i]) == true)
					break ;
			}
			i++;
		}
	}
	if (err.v.ks == true)
		print_builtin_error(&err, MSHL_DLG_ERR_EXPORT);
	return (err.v.num);
}
