/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_03.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:12:20 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 15:48:18 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	set_var_tmp(t_err *err, char *dir, char **s_tmp
	, register int idx)
{
	*s_tmp = ft_substr(dir, 0, idx);
	if (*s_tmp == NULL)
	{
		set_err_var_01(err, true, NORMAL, 1);
		err->v.str = MSHL_EINVAL;
		return (true);
	}
	return (false);
}

static t_bool	get_dir_prev(char **dir, t_err *err)
{
	register int	i;
	register int	len_s;
	t_bool			ks;
	char			*s_tmp;

	i = 0;
	s_tmp = NULL;
	if (!*dir)
	{
		set_err_std_01(err);
		return (true);
	}
	len_s = ft_strlen(*dir);
	i = len_s;
	while ((i > 0) && ((*dir)[i] != '/'))
		i--;
	if (set_var_tmp(err, *dir, &s_tmp, i) == true)
		return (true);
	free_str(dir);
	ks = set_str_arg_builtin(err, dir, s_tmp);
	free(s_tmp);
	return (ks);
}

t_bool	try_loop_dir(t_err *err, char **dir, register size_t len_s)
{
	while (len_s != 0)
	{
		if (get_dir_prev(dir, err) == true)
			return (true);
		if (access(*dir, F_OK | R_OK) != ERR)
			return (false);
	}
	return (false);
}

t_bool	try_set_parent_dir(t_data *dt, char **dir, t_err *err)
{
	register size_t	len_s;

	len_s = 0;
	*dir = get_env_var(dt, "PWD");
	if (*dir == NULL)
	{
		*dir = get_env_var(dt, dt->var.home);
		if (*dir == NULL)
		{
			*dir = get_env_var(dt, "/");
			if (*dir == NULL)
			{
				set_err_cd_02(err);
				return (true);
			}
		}
	}
	else
		if (try_loop_dir(err, dir, len_s) == true)
			return (true);
	return (false);
}
