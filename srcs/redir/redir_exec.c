/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:37:41 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 08:51:21 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_fds_intro_multiple_blocs(t_data *dt, t_exec *exec)
{
	if (exec->count_bloc == 1)
	{
		close_fd(dt, exec->io.out_curr_fd);
		exec->io.out_curr_fd = exec->io.pipe_fds[1];
	}	
	else if (exec->count_bloc != exec->nb_blocs)
	{	
		exec->io.out_curr_fd = exec->io.pipe_fds[1];
		exec->io.in_curr_fd = exec->io.old_pipe_in;
	}
	else if (exec->count_bloc == (int)exec->nb_blocs)
	{
		close_fd(dt, exec->io.pipe_fds[1]);
		close_fd(dt, exec->io.pipe_fds[0]);
		exec->io.in_curr_fd = exec->io.old_pipe_in;
		exec->io.out_curr_fd = dup(1);
	}
}

t_bool	set_fds_intro(t_data *dt, t_exec *exec)
{
	t_bool	ks;

	ks = false;
	if (exec->nb_blocs == 1)
	{
		close_fd(dt, exec->io.pipe_fds[0]);
		close_fd(dt, exec->io.pipe_fds[1]);
	}
	else if ((int)exec->nb_blocs > 1)
		set_fds_intro_multiple_blocs(dt, exec);
	return (ks);
}

static void	set_fds_outro_multiple_blocs(t_data *dt, t_exec *exec)
{
	if (exec->count_bloc == 1)
	{
		close_fd(dt, exec->io.pipe_fds[1]);
		close_fd(dt, exec->io.in_curr_fd);
		exec->io.old_pipe_in = exec->io.pipe_fds[0];
	}
	else if (exec->count_bloc != exec->nb_blocs)
	{
		close_fd(dt, exec->io.pipe_fds[1]);
		close_fd(dt, exec->io.old_pipe_in);
		exec->io.old_pipe_in = exec->io.pipe_fds[0];
		exec->io.in_curr_fd = exec->io.pipe_fds[0];
	}
	else if (exec->count_bloc == exec->nb_blocs)
	{
		close_fd(dt, exec->io.old_pipe_in);
		close_fd(dt, exec->io.out_curr_fd);
	}
}

t_bool	set_fds_outro(t_data *dt, t_exec *exec)
{
	t_bool	ks;

	ks = false;
	if (exec->nb_blocs == 1)
	{	
		close_fd(dt, exec->io.in_curr_fd);
		close_fd(dt, exec->io.out_curr_fd);
	}
	else if (exec->nb_blocs > 1)
		set_fds_outro_multiple_blocs(dt, exec);
	return (ks);
}
