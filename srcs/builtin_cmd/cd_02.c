/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:40 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:03:52 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_getcwd(t_data *dt, char **cdir, t_err *err)
{
	*cdir = getcwd(NULL, 0);
	if (*cdir == NULL)
	{
		set_err_var_01(err, true, NORMAL, errno);
		err->v.str = strerror(errno);
		if (try_set_parent_dir(dt, cdir, err) == true)
			return (true);
	}
	return (false);
}

static t_bool	ft_replace_dir(t_data *dt, t_err *err, char **dir)
{
	if (dt->var.home != NULL)
	{
		if (set_str_arg(err, dir, dt->var.home) == true)
			return (true);
	}
	else
	{
		set_err_cd_01(err);
		return (true);
	}
	return (false);
}

t_chk_str	chk_def_dir(t_data *dt, t_err *err, char **dir, char **cdir)
{
	t_chk_str	chk;

	chk.ks = false;
	chk.idx = false;
	if (!*dir)
	{
		chk.idx = true;
		if (ft_replace_dir(dt, err, dir) == true)
			chk.ks = true;
	}
	else
		get_pwd(dt);
	if (chk.ks == false)
	{
		if (ft_getcwd(dt, cdir, err) == true)
			chk.ks = true;
	}
	return (chk);
}
