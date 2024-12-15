/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:56:20 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/20 15:11:07 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_ve_pwd(t_data *dt, t_err *err)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (!new_path)
	{	
		set_err_var_01(err, true, CRITICAL, errno);
		err->v.str = strerror(errno);
	}
	if (set_env_var(dt, (char *[]){"PWD", new_path, NULL}))
	{
		set_err_var_01(err, true, CRITICAL, errno);
		err->v.str = strerror(errno);
	}
	free_str(&dt->var.pwd);
	set_str_arg_builtin(err, &dt->var.pwd, new_path);
	free(new_path);
}

void	update_ve_oldpwd(t_data *dt, char *old_dir, t_err *err)
{
	if (set_env_var(dt, (char *[]){"OLDPWD", old_dir, NULL}))
	{
		set_err_var_01(err, true, CRITICAL, errno);
		err->v.str = strerror(errno);
	}
}

t_bool	ft_chdir(t_data *dt, char *path_dest, t_err *err)
{	
	if (access(path_dest, F_OK | R_OK) == ERR)
	{
		set_err_var_01(err, true, CRITICAL, errno);
		dt->err.v.str = strerror(errno);
		return (true);
	}
	if (chdir(path_dest))
	{
		set_err_var_01(err, true, NORMAL, errno);
		err->v.str = strerror(errno);
		return (true);
	}
	return (false);
}

static t_bool	ft_cd_core(t_data *dt, t_err *err, char **dest_path)
{
	t_chk_str	chk;
	char		*cdir;

	cdir = NULL;
	chk = chk_def_dir(dt, err, dest_path, &cdir);
	if (chk.ks == false)
	{
		if (ft_chdir(dt, *dest_path, err) == false)
		{
			update_ve_pwd(dt, err);
			update_ve_oldpwd(dt, cdir, err);
		}
	}
	free_str(&cdir);
	free_str(dest_path);
	return (chk.ks);
}

int	ft_cd(t_data *dt, char **var_name)
{
	t_err		err;
	t_bool		ks;
	char		*dest_path;

	ks = false;
	init_error_data(&err);
	if (ft_tablen(var_name) > 2)
		set_err_cd_03(&err);
	else
	{
		if (var_name[0] == NULL)
			dest_path = NULL;
		else
		{
			if (set_str_arg(&err, &dest_path, var_name[0]) == true)
				ks = true;
		}
		if (ks == false)
			ft_cd_core(dt, &err, &dest_path);
	}
	if (err.v.ks == true)
		print_builtin_error(&err, MSHL_DLG_ERR_CD);
	return (err.v.num);
}
