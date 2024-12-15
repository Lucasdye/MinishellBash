/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:46:12 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/19 16:38:28 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	check_path_forbiden(t_data *dt, t_chk_str *chk, char *cmd)
{
	if ((ft_strchk(cmd, ".") == true) || (ft_strchk(cmd, "..") == true))
	{
		set_err_cmd_01(dt, cmd);
		chk->ks = true;
		return (true);
	}
	if ((ft_strchk(cmd, "./") == true) || (ft_strchk(cmd, "../") == true))
	{
		set_err_cmd_03(dt, cmd);
		chk->ks = true;
		return (true);
	}
	return (false);
}

static t_bool	check_path_01(t_data *dt, t_chk_str *chk, char *cmd)
{
	if (access(cmd, F_OK) != ERR)
	{
		if (access(cmd, X_OK) == ERR)
		{
			set_err_cmd_02(dt);
			chk->ks = true;
			return (true);
		}
		chk->idx = true;
	}
	return (false);
}

static t_bool	check_path_loop(t_data *dt, t_chk_str *chk, char **cmd
	, char *f_path)
{
	if (access(f_path, F_OK) != ERR)
	{
		if (access(f_path, X_OK) != ERR)
		{
			free_str(cmd);
			if (set_str_arg(&dt->err, cmd, f_path) == true)
				chk->ks = true;
			else
				chk->idx = true;
		}
		else
		{
			set_err_cmd_02(dt);
			chk->ks = true;
		}
		return (true);
	}
	return (false);
}

static t_chk_str	ft_chk_path(t_data *dt, char **cmd)
{
	int			i;
	t_chk_str	chk;
	char		**full_paths;

	full_paths = NULL;
	chk.ks = false;
	chk.idx = false;
	i = 0;
	if (check_path_forbiden(dt, &chk, *cmd) == true)
		return (chk);
	if ((check_path_01(dt, &chk, *cmd) == true) || (chk.idx == true))
		return (chk);
	if (ft_clean_path_cmd_02(dt, &chk, *cmd) == true)
		return (chk);
	full_paths = ft_merge_path_cmd(dt, dt->var.path, *cmd);
	while (full_paths[i])
	{	
		if (check_path_loop(dt, &chk, cmd, full_paths[i]) == true)
			break ;
		i++;
	}
	free_tab((void *)full_paths);
	return (chk);
}

t_bool	ft_execve(t_data *dt, char *cmd, char **arg)
{
	t_chk_str	chk;
	t_bool		ks;

	ks = false;
	if (cmd[0] != '\0')
	{
		if (get_path(dt) == true)
			return (true);
		chk = ft_chk_path(dt, &cmd);
		if (chk.ks == true)
			return (true);
		if (chk.idx == true)
		{
			if (execve(cmd, arg, dt->env.tab) == ERR)
			{
				set_err_cmd_02(dt);
				return (true);
			}
		}
		else
			ks = set_err_cmd_01(dt, cmd);
		return (ks);
	}
	set_err_cmd_01(dt, cmd);
	return (true);
}
