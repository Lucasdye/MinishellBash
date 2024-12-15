/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:44:07 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:47:39 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	redirect_input(t_data *dt, t_exec *exec)
{
	t_bool	ks;

	ks = false;
	if (dup2_src_fd_noc(dt, &exec->io.in_curr_fd, STDIN_FILENO) == true)
		return (true);
	if (exec->io.in_curr_fd != 0)
		ks = close_fd(dt, exec->io.in_curr_fd);
	return (ks);
}

static t_bool	redirect_output(t_data *dt, t_exec *exec)
{
	t_bool	ks;

	ks = false;
	if (dup2_src_fd_noc(dt, &exec->io.out_curr_fd, STDOUT_FILENO) == true)
		return (true);
	if (exec->io.out_curr_fd != 1)
		ks = close_fd(dt, exec->io.out_curr_fd);
	return (ks);
}

t_bool	ft_dup2(t_data *dt, t_exec *exec)
{
	if (redirect_input(dt, exec) == true)
		return (true);
	if (redirect_output(dt, exec) == true)
		return (true);
	return (false);
}
