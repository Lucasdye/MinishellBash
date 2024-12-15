/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:53:40 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 17:40:59 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	redir_shell(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	exec->io.backup_in = dup(STDIN_FILENO);
	exec->io.backup_out = dup(STDOUT_FILENO);
	if (redirections_loop(dt, tk, exec) == true)
	{	
		close_fd(dt, exec->io.backup_in);
		close_fd(dt, exec->io.backup_out);
		return (true);
	}
	if (ft_dup2(dt, exec) == true)
	{	
		close_fd(dt, exec->io.backup_in);
		close_fd(dt, exec->io.backup_out);
		return (true);
	}
	return (false);
}

static t_bool	exec_shell(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	if (redir_shell(dt, tk, exec))
		return (true);
	set_idx_to_cmd(tk, exec);
	if (tk->tab[exec->idx].type == tk_cmd_b)
		(*dt->parse.ftab[tk->tab[exec->idx].subtype].func)(dt
			, tk->tab[exec->idx].arg);
	dup2(exec->io.backup_in, STDIN_FILENO);
	close_fd(dt, exec->io.backup_in);
	dup2(exec->io.backup_out, STDOUT_FILENO);
	close_fd(dt, exec->io.backup_out);
	if (dt->err.v.ks == true)
		return (true);
	return (false);
}

static t_bool	simple_command(t_data *dt, t_tk_tab *tk, t_exec *exec)
{
	(void)dt;
	set_idx_to_cmd(tk, exec);
	if (tk->tab[exec->idx].type == tk_cmd_b)
		exec_shell(dt, tk, exec);
	else
		exec_subshell(dt, tk, exec);
	close_all_her_fds(dt, exec);
	if (dt->err.v.ks == true)
		return (true);
	return (false);
}

t_bool	exec(t_data *dt, t_tk_tab *tk)
{	
	t_exec	exec;

	init_exec(&dt->parse.tk, &exec);
	set_idx_to_cmd(tk, &exec);
	if (!((tk->tab[exec.idx].type == tk_cmd_b)
			&& (tk->tab[exec.idx].subtype == c_exit)))
		dt->last_err = 0;
	exec.idx = 0;
	exec.io.in_curr_fd = dup(STDIN_FILENO);
	exec.io.out_curr_fd = dup(STDOUT_FILENO);
	if (is_pipe(&dt->parse.tk))
	{	
		exec_subshell(dt, tk, &exec);
		close_all_her_fds(dt, &exec);
	}
	else
		simple_command(dt, tk, &exec);
	if (dt->err.v.ks == true)
		return (true);
	return (false);
}
