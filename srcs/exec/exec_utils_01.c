/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:04:17 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:09:02 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_io(t_exec *exec)
{
	exec->io.in_start = 0;
	exec->io.out_start = 1;
	exec->io.in_curr_fd = 0;
	exec->io.out_curr_fd = 1;
	exec->io.pipe_fds[0] = 0;
	exec->io.pipe_fds[1] = 1;
}

void	init_exec(t_tk_tab *tk, t_exec *exec)
{
	exec->nb_blocs = count_blocs_in_command_line(tk);
	exec->count_bloc = 1;
	exec->idx = 0;
	exec->idx_pid = 0;
	exec->exit_code = 0;
	exec->signal_code = 0;
	exec->flg_hd = false;
	init_io(exec);
}

void	set_idx_to_bloc(t_tk_tab *tk, t_exec *exec)
{
	int	curr_bloc;

	exec->idx = 0;
	curr_bloc = 1;
	if (exec->count_bloc > 1)
	{
		while (exec->idx < (int)tk->idx && curr_bloc < exec->count_bloc)
		{
			if ((tk->tab[exec->idx].type == tk_redir_op)
				&& (tk->tab[exec->idx].subtype == redir_pipe))
				curr_bloc++;
			exec->idx++;
		}
	}
}

void	set_idx_to_cmd(t_tk_tab *tk, t_exec *exec)
{
	set_idx_to_bloc(tk, exec);
	while (exec->idx < (int)tk->idx)
	{
		if (tk->tab[exec->idx].type == tk_cmd)
			break ;
		if (tk->tab[exec->idx].type == tk_cmd_b)
			break ;
		if ((tk->tab[exec->idx].type == tk_redir_op)
			&& (tk->tab[exec->idx].subtype == redir_pipe))
			break ;
		exec->idx++;
	}
}

void	ft_waitpid(t_data *dt, t_exec *exec)
{
	int	i;

	(void)dt;
	i = 0;
	while (i < (exec->nb_blocs))
	{	
		waitpid(-1, &exec->status, 0);
		if (WIFEXITED(exec->status))
			exec->exit_code = WEXITSTATUS(exec->status);
		else if (WIFSIGNALED(exec->status))
			exec->signal_code = WTERMSIG(exec->status);
		i++;
	}
	if ((exec->signal_code != 0) && (exec->signal_code != 131))
		g_status = exec->signal_code >> 8;
	else
		g_status = exec->exit_code;
	return ;
}
