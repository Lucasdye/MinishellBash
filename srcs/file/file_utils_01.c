/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:33:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 10:59:49 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	close_fd(t_data *dt, int fd)
{
	if (close(fd) == ERR)
	{
		set_err_var_01(&dt->err, true, CRITICAL, errno);
		dt->err.v.str = strerror(errno);
		log_hist_err(&dt->err);
		return (true);
	}
	return (false);
}

void	close_file(t_data *dt)
{
	close_fd(dt, dt->var.fd.in);
	close_fd(dt, dt->var.fd.out);
	return ;
}

t_bool	close_fd_all(t_data *dt, t_pipe p)
{
	if (close_fd(dt, p.fd[0]) == true)
		return (true);
	if (close_fd(dt, p.fd[1]) == true)
		return (true);
	return (false);
}
