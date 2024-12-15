/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:26:32 by lbouguet          #+#    #+#             */
/*   Updated: 2023/11/21 07:54:02 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigquit_child(int signum)
{
	if (signum == SIGQUIT)
	{
		exit(g_status);
	}
}

static void	ft_close_for_her(t_data *dt, t_exec *exec)
{
	if (!exec->flg_hd)
		close_all_her_fds(dt, exec);
	else
		close_all_her_fds_but_current(dt, exec);
	if (exec->nb_blocs != 1 || exec->count_bloc != exec->nb_blocs)
	{	
		close(exec->io.pipe_fds[0]);
		close(exec->io.pipe_fds[1]);
	}
	return ;
}

static t_bool	child(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	int	return_code;

	return_code = 0;
	signal(SIGQUIT, &handle_sigquit_child);
	if (redirections_loop(dt, tk, exec))
		return_code = dt->err.v.num;
	else
	{
		ft_dup2(dt, exec);
		ft_close_for_her(dt, exec);
		set_idx_to_cmd(tk, exec);
		if (tk->tab[exec->idx].type == tk_cmd_b && dt->err.v.ks == false)
			return_code = (*dt->parse.ftab[tk->tab[exec->idx]
					.subtype].func)(dt, tk->tab[exec->idx].arg);
		else if (tk->tab[exec->idx].type == tk_cmd && dt->err.v.ks == false)
		{	
			if (ft_execve(dt, tk->tab[exec->idx].name, tk->tab[exec->idx].arg))
				return_code = dt->err.v.num;
		}
	}
	dt->ks_end = true;
	exit_free(dt, return_code);
	return (return_code);
}

static t_bool	parent(t_data *dt, t_exec *exec)
{
	signal(SIGINT, SIG_IGN);
	if (set_fds_outro(dt, exec) == false)
		return (false);
	return (true);
}

t_bool	exec_subshell(t_data *dt, t_tk_tab *tk, t_exec *exec)
{	
	pid_t		pid;
	t_bool		ks;

	ks = false;
	while (exec->count_bloc <= (int)exec->nb_blocs && !ks)
	{
		pipe(exec->io.pipe_fds);
		set_fds_intro(dt, exec);
		pid = fork();
		if (pid == ERR)
			return (set_err_std_01(&dt->err), true);
		else if (pid == 0)
			child(dt, tk, exec);
		else
			ks = parent(dt, exec);
		exec->count_bloc++;
		exec->idx_pid++;
	}
	ft_waitpid(dt, exec);
	return (ks);
}
