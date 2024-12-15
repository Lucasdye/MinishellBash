/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_mini.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:17:47 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/16 17:55:36 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	close_p(t_data *dt, int fd)
{
	if (close(fd) == ERR)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	return (false);
}

static t_bool	child_mini(t_data *dt, char *cmd, char **arg, t_fd p)
{
	t_bool	ks;

	ft_init_sig(false, true);
	if (close_p(dt, p[fdin]) == true)
		return (true);
	if (dup2_src_fd(dt, &p[fdout], STDOUT_FILENO) == true)
		return (true);
	ks = ft_execve(dt, cmd, arg);
	return (ks);
}

static t_bool	parent_mini(t_data *dt, char **var, t_fd p)
{
	int		status;
	t_bool	ks;

	ks = close_p(dt, p[fdout]);
	if (ks == false)
	{
		waitpid(-1, &status, 0);
		status_child(status);
		if (!WTERMSIG(status))
			ft_get_info(dt, var, p[fdin]);
		else
			ks = true;
		if (close_p(dt, p[fdin]) == true)
			ks = true;
	}	
	return (ks);
}

t_bool	exec_mini(t_data *dt, char **var, char *cmd, char **arg)
{
	int		execpid;
	t_fd	p;
	t_bool	ks;

	ks = false;
	if (pipe(p) == ERR)
	{
		set_err_std_01(&dt->err);
		return (true);
	}
	execpid = fork();
	if (execpid == ERR)
	{
		set_err_std_01(&dt->err);
		close_p(dt, p[fdin]);
		close_p(dt, p[fdout]);
		return (true);
	}
	if (!execpid)
	{
		ks = child_mini(dt, cmd, arg, p);
		return (ks);
	}
	ks = parent_mini(dt, var, p);
	return (ks);
}
