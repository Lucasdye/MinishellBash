/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:24:49 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 08:14:24 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_close_redir(t_data *dt, t_exec *exec, int *fd)
{
	t_bool	ks;

	ks = false;
	if (exec->io.in_curr_fd == -1)
	{	
		ks = close_fd(dt, *fd);
		ks = close_fd(dt, exec->io.out_curr_fd);
		if (exec->nb_blocs > 1 && exec->count_bloc != exec->nb_blocs)
			ks = close_fd(dt, exec->io.pipe_fds[0]);
		if (exec->flg_hd == 2)
			close_all_her_fds_but_current(dt, exec);
		else
			close_all_her_fds(dt, exec);
	}
	else
		ks = close_fd(dt, *fd);
	return (ks);
}

static t_bool	redirection_input(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	int	temp_fd_close;

	temp_fd_close = exec->io.in_curr_fd;
	if (tk->tab[exec->idx].subtype == 3 && !exec->flg_hd)
	{
		exec->io.in_curr_fd = dt->hd.fd[exec->count_bloc - 1];
		exec->flg_hd = true;
	}
	if (dt->err.v.ks == false && tk->tab[exec->idx].subtype == redir_l)
	{	
		if (exec->flg_hd)
			exec->flg_hd = 2;
		file_ops(dt, tk->tab[exec->idx].arg[1], &exec->io.in_curr_fd, READ);
	}
	if (exec->io.in_curr_fd != temp_fd_close)
		ft_close_redir(dt, exec, &temp_fd_close);
	if (dt->err.v.ks)
		return (true);
	return (false);
}

static t_bool	redirection_output(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	int	temp_fd_close;

	temp_fd_close = exec->io.out_curr_fd;
	if (tk->tab[exec->idx].subtype == redir_r)
		file_ops(dt, tk->tab[exec->idx].arg[1], &exec->io.out_curr_fd, WRITE);
	if (tk->tab[exec->idx].subtype == redir_app)
		file_ops(dt, tk->tab[exec->idx].arg[1], &exec->io.out_curr_fd, APPEND);
	if (exec->io.out_curr_fd != temp_fd_close)
		ft_close_redir(dt, exec, &temp_fd_close);
	if (dt->err.v.ks)
		return (true);
	return (false);
}

t_bool	redirections_loop(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	set_idx_to_bloc(tk, exec);
	exec->flg_hd = false;
	while (!((tk->tab[exec->idx].type == tk_redir_op)
			&& (tk->tab[exec->idx].subtype == redir_pipe))
		&& (exec->idx < (int)tk->idx))
	{
		if (dt->err.v.ks == true)
			break ;
		if (tk->tab[exec->idx].type == tk_redir_op)
		{
			if (tk->tab[exec->idx].subtype == redir_l
				|| tk->tab[exec->idx].subtype == redir_inp)
				redirection_input(dt, tk, exec);
			if (tk->tab[exec->idx].subtype == redir_r
				|| tk->tab[exec->idx].subtype == redir_app)
				redirection_output(dt, tk, exec);
		}
		exec->idx++;
	}
	if (dt->err.v.ks == true)
		return (true);
	else
		return (false);
}
